switch (arizona->type) {
#ifdef CONFIG_MFD_WM5102
	case WM5102:
		aod = &wm5102_aod;
		irq = &wm5102_irq;

		arizona->ctrlif_error = false;
		break;
#endif
#ifdef CONFIG_MFD_WM5110
	case WM5110:
	case WM8280:
		aod = &wm5110_aod;

		switch (arizona->rev) {
		case 0 ... 2:
			irq = &wm5110_irq;
			break;
		default:
			irq = &wm5110_revd_irq;
			break;
		}

		arizona->ctrlif_error = false;
		break;
#endif
#ifdef CONFIG_MFD_WM8997
	case WM8997:
		aod = &wm8997_aod;
		irq = &wm8997_irq;

		arizona->ctrlif_error = false;
		break;
#endif
#ifdef CONFIG_MFD_WM8998
	case WM8998:
	case WM1814:
		aod = &wm8998_aod;
		irq = &wm8998_irq;

		arizona->ctrlif_error = false;
		break;
#endif
	default:
		BUG_ON("Unknown Arizona class device" == NULL);
		return -EINVAL;
	}
