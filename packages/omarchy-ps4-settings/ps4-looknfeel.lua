-- Avoid unnecessary GPU work on the PS4 legacy DCE8 display path.
hl.config({
  animations = {
    enabled = false,
  },
})

-- omarchy-launch-about only auto-fits the About window when the user has no
-- fastfetch config of their own. PS4 ships one, which turns that auto-fit off and
-- leaves About on the generic 920x480 float rule, clipping the layout
-- (disableLinewrap truncates rather than wraps). So size it here instead.
--
-- Measured with the PS4 defaults -- foot, JetBrainsMono Nerd Font size 9,
-- pad=14x14 -- giving a 7x17 px cell and 28x28 px of chrome. The About content is
-- 2 + 54 (logo) + 6 + 54 (modules) = 116 columns by max(26 + 2, 32) + 1 = 33 rows,
-- plus a column and a row of slack.
hl.window_rule({
  match = { class = "org.omarchy.about" },
  size = { 117 * 7 + 28, 34 * 17 + 28 },
})
