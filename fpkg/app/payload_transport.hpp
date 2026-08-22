#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

namespace omarchy_ps4 {

using WriteOperation = std::function<std::ptrdiff_t(const std::uint8_t*, std::size_t)>;

// GoldHEN's in-console loopback path must receive the ELF from one application
// write. The platform adapter must prove its socket send buffer can queue the
// entire payload before it connects. A short write is terminal and is never
// retried on the same connection.
bool send_once(const std::uint8_t* bytes, std::size_t size,
               const WriteOperation& write);

}  // namespace omarchy_ps4
