switch (mode) {
#ifdef CONFIG_MFD_WM8351_CONFIG_MODE_0
		case 0:
			reg_map = wm8351_mode0_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8351_CONFIG_MODE_1
		case 1:
			reg_map = wm8351_mode1_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8351_CONFIG_MODE_2
		case 2:
			reg_map = wm8351_mode2_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8351_CONFIG_MODE_3
		case 3:
			reg_map = wm8351_mode3_defaults;
			break;
#endif
		default:
			dev_err(wm8350->dev,
				"WM8351 configuration mode %d not supported\n",
				mode);
			return -EINVAL;
		}
