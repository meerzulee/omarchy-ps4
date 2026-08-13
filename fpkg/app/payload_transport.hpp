#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

namespace omarchy_ps4 {

using WriteOperation = std::function<std::ptrdiff_t(const std::uint8_t*, std::size_t)>;

// Repeats short writes until the complete ELF has reached PayLoader. The
// platform adapter owns socket creation, timeouts and error reporting.
bool send_complete(const std::uint8_t* bytes, std::size_t size, const WriteOperation& write);

}  // namespace omarchy_ps4
