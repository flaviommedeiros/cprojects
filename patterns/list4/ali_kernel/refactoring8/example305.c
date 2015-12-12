static const struct mux_config dm355_pins[] = {
#ifdef CONFIG_DAVINCI_MUX
MUX_CFG(DM355,	MMCSD0,		4,   2,     1,	  0,	 false)

MUX_CFG(DM355,	SD1_CLK,	3,   6,     1,	  1,	 false)
MUX_CFG(DM355,	SD1_CMD,	3,   7,     1,	  1,	 false)
MUX_CFG(DM355,	SD1_DATA3,	3,   8,     3,	  1,	 false)
MUX_CFG(DM355,	SD1_DATA2,	3,   10,    3,	  1,	 false)
MUX_CFG(DM355,	SD1_DATA1,	3,   12,    3,	  1,	 false)
MUX_CFG(DM355,	SD1_DATA0,	3,   14,    3,	  1,	 false)

MUX_CFG(DM355,	I2C_SDA,	3,   19,    1,	  1,	 false)
MUX_CFG(DM355,	I2C_SCL,	3,   20,    1,	  1,	 false)

MUX_CFG(DM355,	MCBSP0_BDX,	3,   0,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_X,	3,   1,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_BFSX,	3,   2,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_BDR,	3,   3,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_R,	3,   4,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_BFSR,	3,   5,     1,	  1,	 false)

MUX_CFG(DM355,	SPI0_SDI,	4,   1,     1,    0,	 false)
MUX_CFG(DM355,	SPI0_SDENA0,	4,   0,     1,    0,	 false)
MUX_CFG(DM355,	SPI0_SDENA1,	3,   28,    1,    1,	 false)

INT_CFG(DM355,  INT_EDMA_CC,	      2,    1,    1,     false)
INT_CFG(DM355,  INT_EDMA_TC0_ERR,     3,    1,    1,     false)
INT_CFG(DM355,  INT_EDMA_TC1_ERR,     4,    1,    1,     false)

EVT_CFG(DM355,  EVT8_ASP1_TX,	      0,    1,    0,     false)
EVT_CFG(DM355,  EVT9_ASP1_RX,	      1,    1,    0,     false)
EVT_CFG(DM355,  EVT26_MMC0_RX,	      2,    1,    0,     false)

MUX_CFG(DM355,	VOUT_FIELD,	1,   18,    3,	  1,	 false)
MUX_CFG(DM355,	VOUT_FIELD_G70,	1,   18,    3,	  0,	 false)
MUX_CFG(DM355,	VOUT_HVSYNC,	1,   16,    1,	  0,	 false)
MUX_CFG(DM355,	VOUT_COUTL_EN,	1,   0,     0xff, 0x55,  false)
MUX_CFG(DM355,	VOUT_COUTH_EN,	1,   8,     0xff, 0x55,  false)

MUX_CFG(DM355,	VIN_PCLK,	0,   14,    1,    1,	 false)
MUX_CFG(DM355,	VIN_CAM_WEN,	0,   13,    1,    1,	 false)
MUX_CFG(DM355,	VIN_CAM_VD,	0,   12,    1,    1,	 false)
MUX_CFG(DM355,	VIN_CAM_HD,	0,   11,    1,    1,	 false)
MUX_CFG(DM355,	VIN_YIN_EN,	0,   10,    1,    1,	 false)
MUX_CFG(DM355,	VIN_CINL_EN,	0,   0,   0xff, 0x55,	 false)
MUX_CFG(DM355,	VIN_CINH_EN,	0,   8,     3,    3,	 false)
#endif
};
