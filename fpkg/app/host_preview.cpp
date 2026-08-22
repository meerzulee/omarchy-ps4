#include "manager_state.hpp"
#include "payload_transport.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

using omarchy_ps4::Action;
using omarchy_ps4::ManagerState;
using omarchy_ps4::Phase;

namespace {

bool check(bool value, const char* message) {
  if (!value) std::cerr << "FAIL: " << message << '\n';
  return value;
}

int self_test() {
  bool ok = true;
  ManagerState install = omarchy_ps4::begin(Action::Install);
  const std::array<Phase, 10> install_path = {
      Phase::Preflight, Phase::Release, Phase::Storage, Phase::Download,
      Phase::Verify, Phase::Stage, Phase::Ready, Phase::PayloaderCheck,
      Phase::SendElf, Phase::Kexec};
  for (Phase expected : install_path) {
    ok &= check(install.phase == expected, "install path differs from protocol");
    if (!omarchy_ps4::terminal(install.phase)) install = omarchy_ps4::advance(install);
  }
  ok &= check(install.progress == 100, "install path did not finish");

  ManagerState boot = omarchy_ps4::begin(Action::Boot);
  ok &= check(boot.phase == Phase::Ready, "boot must use verified release");
  boot = omarchy_ps4::advance(boot);
  ok &= check(boot.phase == Phase::PayloaderCheck, "boot must check GoldHEN before send");

  ManagerState repair = omarchy_ps4::begin(Action::Repair);
  repair = omarchy_ps4::advance(repair);
  ok &= check(repair.phase == Phase::Restore, "repair must enter restore");
  repair = omarchy_ps4::advance(repair);
  ok &= check(repair.phase == Phase::Ready, "repair must return a verified release");

  const std::array<std::uint8_t, 31> elf_bytes{};
  std::vector<std::uint8_t> received;
  std::size_t write_calls = 0;
  ok &= check(!omarchy_ps4::send_once(
      elf_bytes.data(), elf_bytes.size(),
      [&received, &write_calls](const std::uint8_t* bytes,
                               std::size_t size) -> std::ptrdiff_t {
        ++write_calls;
        const std::size_t short_write = std::min<std::size_t>(size, 7);
        received.insert(received.end(), bytes, bytes + short_write);
        return static_cast<std::ptrdiff_t>(short_write);
      }), "payload transport retried or accepted a dangerous short write");
  ok &= check(write_calls == 1, "payload transport retried a short write");
  ok &= check(received.size() == 7, "payload transport wrote after a short write");

  received.clear();
  write_calls = 0;
  ok &= check(omarchy_ps4::send_once(
      elf_bytes.data(), elf_bytes.size(),
      [&received, &write_calls](const std::uint8_t* bytes,
                               std::size_t size) -> std::ptrdiff_t {
        ++write_calls;
        received.insert(received.end(), bytes, bytes + size);
        return static_cast<std::ptrdiff_t>(size);
      }), "payload transport rejected one complete write");
  ok &= check(write_calls == 1, "payload transport used more than one write");
  ok &= check(received.size() == elf_bytes.size(),
              "payload transport truncated a complete write");
  ok &= check(!omarchy_ps4::send_once(
      elf_bytes.data(), elf_bytes.size(),
      [](const std::uint8_t*, std::size_t) -> std::ptrdiff_t { return 0; }),
      "payload transport accepted a closed socket");

  std::cout << (ok ? "manager-state: OK\n" : "manager-state: FAIL\n");
  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}

}  // namespace

int main(int argc, char** argv) {
  if (argc > 1 && std::string_view(argv[1]) == "--self-test") return self_test();
  ManagerState state = omarchy_ps4::begin(Action::Install);
  std::cout << "OMARCHY PS4 — host protocol preview\n\n";
  for (;;) {
    std::cout << '[' << omarchy_ps4::label(state.phase) << "] "
              << state.progress << "%  " << state.detail << '\n';
    if (omarchy_ps4::terminal(state.phase)) break;
    state = omarchy_ps4::advance(state);
  }
  return EXIT_SUCCESS;
}
