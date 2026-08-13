-- PS4-safe Quattro startup. Hardware and storage services are enabled only
-- after their individual compatibility gates pass.
hl.on("hyprland.start", function()
  hl.exec_cmd("systemctl --user import-environment $(env | cut -d'=' -f 1)")
  hl.exec_cmd("dbus-update-activation-environment --systemd --all")
  hl.exec_cmd("omarchy-launch-shell")
end)
