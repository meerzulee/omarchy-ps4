-- The PS4 HDMI bridge currently exposes one proven mode.
hl.env("GDK_SCALE", "1")
hl.monitor({
  output = "HDMI-A-1",
  mode = "1920x1080@60",
  position = "0x0",
  scale = 1,
})
