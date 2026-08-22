#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

enum { kSendBufferSize = 1024 * 1024 };

static void usage(const char *program) {
  fprintf(stderr, "usage: %s HOST PORT LOADER.ELF\n", program);
}

int main(int argc, char **argv) {
  if (argc != 4) {
    usage(argv[0]);
    return 64;
  }

  char *port_end = NULL;
  errno = 0;
  const long port = strtol(argv[2], &port_end, 10);
  if (errno != 0 || port_end == argv[2] || *port_end != '\0' || port < 1 ||
      port > 65535) {
    fprintf(stderr, "invalid port: %s\n", argv[2]);
    return 64;
  }

  const int file_fd = open(argv[3], O_RDONLY);
  if (file_fd < 0) {
    perror("open loader");
    return 66;
  }

  struct stat file_stat;
  if (fstat(file_fd, &file_stat) != 0 || file_stat.st_size <= 0) {
    perror("stat loader");
    close(file_fd);
    return 66;
  }
  const size_t size = (size_t)file_stat.st_size;
  const void *bytes = mmap(NULL, size, PROT_READ, MAP_PRIVATE, file_fd, 0);
  if (bytes == MAP_FAILED) {
    perror("map loader");
    close(file_fd);
    return 71;
  }

  const int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("socket");
    munmap((void *)bytes, size);
    close(file_fd);
    return 71;
  }

  const int requested_send_buffer = kSendBufferSize;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_SNDBUF, &requested_send_buffer,
                 sizeof(requested_send_buffer)) != 0) {
    perror("set send buffer");
    close(socket_fd);
    munmap((void *)bytes, size);
    close(file_fd);
    return 71;
  }

#ifdef SO_NOSIGPIPE
  const int no_sigpipe = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_NOSIGPIPE, &no_sigpipe,
                 sizeof(no_sigpipe)) != 0) {
    perror("disable SIGPIPE");
    close(socket_fd);
    munmap((void *)bytes, size);
    close(file_fd);
    return 71;
  }
#endif

  int actual_send_buffer = 0;
  socklen_t option_size = sizeof(actual_send_buffer);
  if (getsockopt(socket_fd, SOL_SOCKET, SO_SNDBUF, &actual_send_buffer,
                 &option_size) != 0) {
    perror("get send buffer");
    close(socket_fd);
    munmap((void *)bytes, size);
    close(file_fd);
    return 71;
  }
  if (actual_send_buffer < (int)size) {
    fprintf(stderr, "send buffer too small: actual=%d required=%zu\n",
            actual_send_buffer, size);
    close(socket_fd);
    munmap((void *)bytes, size);
    close(file_fd);
    return 71;
  }

  struct sockaddr_in address;
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons((unsigned short)port);
  if (inet_pton(AF_INET, argv[1], &address.sin_addr) != 1) {
    fprintf(stderr, "invalid IPv4 address: %s\n", argv[1]);
    close(socket_fd);
    munmap((void *)bytes, size);
    close(file_fd);
    return 64;
  }
  if (connect(socket_fd, (struct sockaddr *)&address, sizeof(address)) != 0) {
    perror("connect");
    close(socket_fd);
    munmap((void *)bytes, size);
    close(file_fd);
    return 69;
  }

  int send_flags = 0;
#ifdef MSG_NOSIGNAL
  send_flags |= MSG_NOSIGNAL;
#endif
  const ssize_t written = send(socket_fd, bytes, size, send_flags);
  const int send_errno = written < 0 ? errno : 0;
  printf("single-write requested=%zu written=%zd send-buffer=%d errno=%d\n",
         size, written, actual_send_buffer, send_errno);

  close(socket_fd);
  munmap((void *)bytes, size);
  close(file_fd);
  return written == (ssize_t)size ? 0 : 74;
}
