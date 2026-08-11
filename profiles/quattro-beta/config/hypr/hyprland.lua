-- Omarchy Quattro for PS4: upstream defaults with PS4-owned overrides.
dofile((os.getenv("OMARCHY_PATH") or "/usr/share/omarchy") .. "/default/hypr/bootstrap.lua")

-- Bindings for applications not included in the reduced PS4 profile stay off.
omarchy_preinstalled_bindings = false

require("default.hypr.omarchy")
require("hypr.monitors")
require("hypr.input")
require("hypr.bindings")
require("hypr.looknfeel")
require("hypr.autostart")
require("default.hypr.toggles")
