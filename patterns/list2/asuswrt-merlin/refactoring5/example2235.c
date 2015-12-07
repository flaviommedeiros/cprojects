#ifdef CONFIG_FB_MATROX_G
if (minfo->devflags.g450dac) {
		hw->DACreg[POS1064_XPWRCTRL] = 0x1F;	/* powerup everything */
		hw->DACreg[POS1064_XOUTPUTCONN] = 0x00;	/* disable outputs */
		hw->DACreg[POS1064_XMISCCTRL] |= M1064_XMISCCTRL_DAC_EN;
		switch (minfo->outputs[0].src) {
			case MATROXFB_SRC_CRTC1:
			case MATROXFB_SRC_CRTC2:
				hw->DACreg[POS1064_XOUTPUTCONN] |= 0x01;	/* enable output; CRTC1/2 selection is in CRTC2 ctl */
				break;
			case MATROXFB_SRC_NONE:
				hw->DACreg[POS1064_XMISCCTRL] &= ~M1064_XMISCCTRL_DAC_EN;
				break;
		}
		switch (minfo->outputs[1].src) {
			case MATROXFB_SRC_CRTC1:
				hw->DACreg[POS1064_XOUTPUTCONN] |= 0x04;
				break;
			case MATROXFB_SRC_CRTC2:
				if (minfo->outputs[1].mode == MATROXFB_OUTPUT_MODE_MONITOR) {
					hw->DACreg[POS1064_XOUTPUTCONN] |= 0x08;
				} else {
					hw->DACreg[POS1064_XOUTPUTCONN] |= 0x0C;
				}
				break;
			case MATROXFB_SRC_NONE:
				hw->DACreg[POS1064_XPWRCTRL] &= ~0x01;		/* Poweroff DAC2 */
				break;
		}
		switch (minfo->outputs[2].src) {
			case MATROXFB_SRC_CRTC1:
				hw->DACreg[POS1064_XOUTPUTCONN] |= 0x20;
				break;
			case MATROXFB_SRC_CRTC2:
				hw->DACreg[POS1064_XOUTPUTCONN] |= 0x40;
				break;
			case MATROXFB_SRC_NONE:
				break;
		}
		/* Now set timming related variables... */
		g450_set_plls(minfo);
	} else
#endif
	{
		if (minfo->outputs[1].src == MATROXFB_SRC_CRTC1) {
			hw->DACreg[POS1064_XPIXCLKCTRL] = M1064_XPIXCLKCTRL_PLL_UP | M1064_XPIXCLKCTRL_EN | M1064_XPIXCLKCTRL_SRC_EXT;
			hw->DACreg[POS1064_XMISCCTRL] |= GX00_XMISCCTRL_MFC_MAFC | G400_XMISCCTRL_VDO_MAFC12;
		} else if (minfo->outputs[1].src == MATROXFB_SRC_CRTC2) {
			hw->DACreg[POS1064_XMISCCTRL] |= GX00_XMISCCTRL_MFC_MAFC | G400_XMISCCTRL_VDO_C2_MAFC12;
		} else if (minfo->outputs[2].src == MATROXFB_SRC_CRTC1)
			hw->DACreg[POS1064_XMISCCTRL] |= GX00_XMISCCTRL_MFC_PANELLINK | G400_XMISCCTRL_VDO_MAFC12;
		else
			hw->DACreg[POS1064_XMISCCTRL] |= GX00_XMISCCTRL_MFC_DIS;

		if (minfo->outputs[0].src != MATROXFB_SRC_NONE)
			hw->DACreg[POS1064_XMISCCTRL] |= M1064_XMISCCTRL_DAC_EN;
	}
