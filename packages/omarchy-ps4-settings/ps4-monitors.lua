-- Keep the accepted mode as the default. Experimental gift images may select
-- the separately-built native-ultrawide kernel through this narrow override.
local display_mode = os.getenv("OMARCHY_PS4_DISPLAY_MODE") or "1920x1080@60"
if display_mode ~= "1920x1080@60" and display_mode ~= "3440x1440@50" then
  display_mode = "1920x1080@60"
end

hl.env("GDK_SCALE", "1")
hl.monitor({
  output = "HDMI-A-1",
  mode = display_mode,
  position = "0x0",
  scale = 1,
})
