#include "payload_transport.hpp"

namespace omarchy_ps4 {

bool send_complete(const std::uint8_t* bytes, std::size_t size, const WriteOperation& write) {
  if ((bytes == nullptr && size != 0) || !write) return false;
  std::size_t offset = 0;
  while (offset < size) {
    const std::ptrdiff_t written = write(bytes + offset, size - offset);
    if (written <= 0 || static_cast<std::size_t>(written) > size - offset) return false;
    offset += static_cast<std::size_t>(written);
  }
  return true;
}

}  // namespace omarchy_ps4
