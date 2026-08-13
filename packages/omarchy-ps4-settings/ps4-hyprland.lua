-- Omarchy Quattro for PS4: upstream desktop with PS4-owned hardware policy.
dofile((os.getenv("OMARCHY_PATH") or "/usr/share/omarchy") .. "/default/hypr/bootstrap.lua")

omarchy_preinstalled_bindings = true

require("default.hypr.omarchy")
require("hypr.monitors")
require("hypr.input")
require("hypr.bindings")
require("hypr.looknfeel")
require("default.hypr.toggles")
