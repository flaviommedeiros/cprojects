switch (arizona->type) {
#ifdef CONFIG_MFD_WM5102
	case WM5102:
		aod = &wm5102_aod;
		irq = &wm5102_irq;

		ctrlif_error = false;
		break;
#endif
#ifdef CONFIG_MFD_WM5110
	case WM5110:
		aod = &wm5110_aod;
		irq = &wm5110_irq;

		ctrlif_error = false;
		break;
#endif
	default:
		BUG_ON("Unknown Arizona class device" == NULL);
		return -EINVAL;
	}
