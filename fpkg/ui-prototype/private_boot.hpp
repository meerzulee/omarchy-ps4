#pragma once

namespace omarchy_ps4 {

enum class BootSendResult {
  Ok,
  OpenFailed,
  SizeMismatch,
  ReadFailed,
  DigestMismatch,
  StageDirectoryFailed,
  StageRecoveryFailed,
  StageWriteFailed,
  StageVerifyFailed,
  StageActivateFailed,
  SocketFailed,
  SocketBufferFailed,
  ConnectFailed,
  SendFailed,
};

enum class InternalBootState {
  Missing,
  Ready,
  UpdateAvailable,
  Interrupted,
  Blocked,
};

BootSendResult stage_internal_boot_set();
InternalBootState inspect_internal_boot_set();
const char* internal_boot_state_name(InternalBootState state);
bool internal_boot_set_ready();
BootSendResult send_embedded_loader();
const char* boot_send_message(BootSendResult result);

}  // namespace omarchy_ps4
