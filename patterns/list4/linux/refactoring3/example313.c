switch (par->pci_id) {
#ifdef CONFIG_FB_ATY_GX
	case PCI_CHIP_MACH64GX:
		if (type != 0x00d7)
			return -ENODEV;
		break;
	case PCI_CHIP_MACH64CX:
		if (type != 0x0057)
			return -ENODEV;
		break;
#endif
#ifdef CONFIG_FB_ATY_CT
	case PCI_CHIP_MACH64VT:
		switch (rev & 0x07) {
		case 0x00:
			switch (rev & 0xc0) {
			case 0x00:
				name = "ATI264VT (A3) (Mach64 VT)";
				par->pll_limits.pll_max = 170;
				par->pll_limits.mclk = 67;
				par->pll_limits.xclk = 67;
				par->pll_limits.ecp_max = 80;
				par->features = ATI_CHIP_264VT;
				break;
			case 0x40:
				name = "ATI264VT2 (A4) (Mach64 VT)";
				par->pll_limits.pll_max = 200;
				par->pll_limits.mclk = 67;
				par->pll_limits.xclk = 67;
				par->pll_limits.ecp_max = 80;
				par->features = ATI_CHIP_264VT | M64F_MAGIC_POSTDIV;
				break;
			}
			break;
		case 0x01:
			name = "ATI264VT3 (B1) (Mach64 VT)";
			par->pll_limits.pll_max = 200;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 80;
			par->features = ATI_CHIP_264VTB;
			break;
		case 0x02:
			name = "ATI264VT3 (B2) (Mach64 VT)";
			par->pll_limits.pll_max = 200;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 80;
			par->features = ATI_CHIP_264VT3;
			break;
		}
		break;
	case PCI_CHIP_MACH64GT:
		switch (rev & 0x07) {
		case 0x01:
			name = "3D RAGE II (Mach64 GT)";
			par->pll_limits.pll_max = 170;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 80;
			par->features = ATI_CHIP_264GTB;
			break;
		case 0x02:
			name = "3D RAGE II+ (Mach64 GT)";
			par->pll_limits.pll_max = 200;
			par->pll_limits.mclk = 67;
			par->pll_limits.xclk = 67;
			par->pll_limits.ecp_max = 100;
			par->features = ATI_CHIP_264GTB;
			break;
		}
		break;
#endif
	}
