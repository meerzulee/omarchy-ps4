# Third-party inputs

| Component | Pinned source | License status | Used by this draft |
| --- | --- | --- | --- |
| Omarchy Quattro | `144f4d1e31d6ddc2cba5dfd69278cabf02bafd05` | MIT | UX/runtime reference; preserve its notice when assets are copied |
| OpenOrbis PS4 Toolchain | v0.5.4 release archive, SHA-256 `3c7cd5bb593ca74fa1c13fd59f3938dc0fc07985167f7275063019e63abe4526` | GPL-3.0; LibOrbisPkg LGPL-3.0; bundled fallback Gontserrat OFL-1.1 | Builds the private UI-only FPKG |
| Sony/Monotype SST | Console-provided `/preinst/common/font/SST-{Roman,Bold}.otf` | Proprietary; loaded read-only at runtime and never copied or bundled | Optional UI font on PS4, with OFL fallback |
| Payload Guest | `f73b7fc701ff1b91e40369486325b440b5816c9e` | GPL-3.0 | Design reference only; no source copied |
| PS4 Linux Loader | `9acef9fbf79097a2bb39d6c9c17228198bc445cc` | No license declared | Private, ignored build input only |

The draft does not grant redistribution rights for any third-party binary.
Public package construction must stop if a component's license is absent or
incompatible with the intended distribution.
