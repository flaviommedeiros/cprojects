static const struct mux_config dm646x_pins[] = {
#ifdef CONFIG_DAVINCI_MUX
MUX_CFG(DM646X, ATAEN,		0,   0,     5,	  1,	 true)

MUX_CFG(DM646X, AUDCK1,		0,   29,    1,	  0,	 false)

MUX_CFG(DM646X, AUDCK0,		0,   28,    1,	  0,	 false)

MUX_CFG(DM646X, CRGMUX,			0,   24,    7,    5,	 true)

MUX_CFG(DM646X, STSOMUX_DISABLE,	0,   22,    3,    0,	 true)

MUX_CFG(DM646X, STSIMUX_DISABLE,	0,   20,    3,    0,	 true)

MUX_CFG(DM646X, PTSOMUX_DISABLE,	0,   18,    3,    0,	 true)

MUX_CFG(DM646X, PTSIMUX_DISABLE,	0,   16,    3,    0,	 true)

MUX_CFG(DM646X, STSOMUX,		0,   22,    3,    2,	 true)

MUX_CFG(DM646X, STSIMUX,		0,   20,    3,    2,	 true)

MUX_CFG(DM646X, PTSOMUX_PARALLEL,	0,   18,    3,    2,	 true)

MUX_CFG(DM646X, PTSIMUX_PARALLEL,	0,   16,    3,    2,	 true)

MUX_CFG(DM646X, PTSOMUX_SERIAL,		0,   18,    3,    3,	 true)

MUX_CFG(DM646X, PTSIMUX_SERIAL,		0,   16,    3,    3,	 true)
#endif
};
