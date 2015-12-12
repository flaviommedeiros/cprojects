switch (reg) {
#ifdef CONFIG_MFD_WM5102
	case 0x5102:
		type_name = "WM5102";
		if (arizona->type != WM5102) {
			dev_err(arizona->dev, "WM5102 registered as %d\n",
				arizona->type);
			arizona->type = WM5102;
		}
		apply_patch = wm5102_patch;
		arizona->rev &= 0x7;
		break;
#endif
#ifdef CONFIG_MFD_WM5110
	case 0x5110:
		type_name = "WM5110";
		if (arizona->type != WM5110) {
			dev_err(arizona->dev, "WM5110 registered as %d\n",
				arizona->type);
			arizona->type = WM5110;
		}
		apply_patch = wm5110_patch;
		break;
#endif
	default:
		dev_err(arizona->dev, "Unknown device ID %x\n", reg);
		goto err_reset;
	}
