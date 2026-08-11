-- Avoid unnecessary GPU load until the PS4 compositor path passes soak tests.
hl.config({
  animations = {
    enabled = false,
  },
})
