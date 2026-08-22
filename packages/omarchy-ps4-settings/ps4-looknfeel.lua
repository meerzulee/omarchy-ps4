-- Avoid unnecessary GPU work on the PS4 legacy DCE8 display path.
hl.config({
  animations = {
    enabled = false,
  },
})
