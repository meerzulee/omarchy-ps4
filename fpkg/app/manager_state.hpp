#pragma once

#include <string_view>

namespace omarchy_ps4 {

enum class Action { Install, Boot, Repair, Diagnostics, About };
enum class Phase {
  Home,
  Preflight,
  Release,
  Storage,
  Download,
  Verify,
  Stage,
  Ready,
  PayloaderCheck,
  SendElf,
  Kexec,
  VerifyLocal,
  Restore,
  Export,
  About,
  Failed,
};

struct ManagerState {
  Phase phase{Phase::Home};
  Action selected{Action::Install};
  unsigned progress{0};
  std::string_view detail{"Choose an action"};
};

ManagerState begin(Action action);
ManagerState advance(ManagerState state);
bool terminal(Phase phase);
std::string_view label(Action action);
std::string_view label(Phase phase);

}  // namespace omarchy_ps4
