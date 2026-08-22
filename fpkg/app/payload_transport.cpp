#include "payload_transport.hpp"

namespace omarchy_ps4 {

bool send_once(const std::uint8_t* bytes, std::size_t size,
               const WriteOperation& write) {
  if ((bytes == nullptr && size != 0) || !write) return false;
  if (size == 0) return true;
  const std::ptrdiff_t written = write(bytes, size);
  return written == static_cast<std::ptrdiff_t>(size);
}

}  // namespace omarchy_ps4
