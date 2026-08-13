#include "manager_state.hpp"

namespace omarchy_ps4 {

ManagerState begin(Action action) {
  switch (action) {
    case Action::Install:
      return {Phase::Preflight, action, 3, "Checking GoldHEN, network and target support"};
    case Action::Boot:
      return {Phase::Ready, action, 92, "Using the last verified release"};
    case Action::Repair:
      return {Phase::VerifyLocal, action, 15, "Checking active and previous boot assets"};
    case Action::Diagnostics:
      return {Phase::Export, action, 40, "Writing a redacted support bundle"};
    case Action::About:
      return {Phase::About, action, 100, "Showing versions, digests, sources and licenses"};
  }
  return {Phase::Failed, action, 0, "Unknown action"};
}

ManagerState advance(ManagerState state) {
  switch (state.phase) {
    case Phase::Home: return begin(state.selected);
    case Phase::Preflight: return {Phase::Release, state.selected, 8, "Fetching the signed release manifest"};
    case Phase::Release: return {Phase::Storage, state.selected, 13, "Confirming external USB target identity"};
    case Phase::Storage: return {Phase::Download, state.selected, 38, "Resuming release artifacts"};
    case Phase::Download: return {Phase::Verify, state.selected, 72, "Checking size, SHA-256 and manifest signature"};
    case Phase::Verify: return {Phase::Stage, state.selected, 84, "Staging boot files and retaining rollback"};
    case Phase::Stage: return {Phase::Ready, state.selected, 92, "Release verified and ready"};
    case Phase::VerifyLocal: return {Phase::Restore, state.selected, 55, "Restoring the last-known-good boot set"};
    case Phase::Restore: return {Phase::Ready, state.selected, 92, "Repair complete"};
    case Phase::Ready: return {Phase::PayloaderCheck, state.selected, 94, "Checking GoldHEN PayLoader on 127.0.0.1:9090"};
    case Phase::PayloaderCheck: return {Phase::SendElf, state.selected, 97, "Sending the pinned Linux loader ELF"};
    case Phase::SendElf: return {Phase::Kexec, state.selected, 100, "Linux is taking over; finish owner setup there"};
    case Phase::Export: return {Phase::Home, state.selected, 100, "Diagnostics exported"};
    case Phase::About: return {Phase::Home, state.selected, 100, "Choose an action"};
    case Phase::Kexec:
    case Phase::Failed:
      return state;
  }
  return {Phase::Failed, state.selected, 0, "Invalid state"};
}

bool terminal(Phase phase) { return phase == Phase::Kexec || phase == Phase::Failed; }

std::string_view label(Action action) {
  switch (action) {
    case Action::Install: return "Install / update";
    case Action::Boot: return "Boot Linux";
    case Action::Repair: return "Repair";
    case Action::Diagnostics: return "Diagnostics";
    case Action::About: return "About";
  }
  return "Unknown";
}

std::string_view label(Phase phase) {
  switch (phase) {
    case Phase::Home: return "HOME";
    case Phase::Preflight: return "PREFLIGHT";
    case Phase::Release: return "RELEASE";
    case Phase::Storage: return "STORAGE";
    case Phase::Download: return "DOWNLOAD";
    case Phase::Verify: return "VERIFY";
    case Phase::Stage: return "STAGE";
    case Phase::Ready: return "READY";
    case Phase::PayloaderCheck: return "PAYLOADER";
    case Phase::SendElf: return "SEND ELF";
    case Phase::Kexec: return "LINUX";
    case Phase::VerifyLocal: return "VERIFY LOCAL";
    case Phase::Restore: return "RESTORE";
    case Phase::Export: return "EXPORT";
    case Phase::About: return "ABOUT";
    case Phase::Failed: return "FAILED";
  }
  return "UNKNOWN";
}

}  // namespace omarchy_ps4
