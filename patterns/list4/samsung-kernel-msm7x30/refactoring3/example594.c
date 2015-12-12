switch (wm->id & 0xff) {
#ifdef CONFIG_TOUCHSCREEN_WM9705
	case 0x05:
		wm->codec = &wm9705_codec;
		break;
#endif
#ifdef CONFIG_TOUCHSCREEN_WM9712
	case 0x12:
		wm->codec = &wm9712_codec;
		break;
#endif
#ifdef CONFIG_TOUCHSCREEN_WM9713
	case 0x13:
		wm->codec = &wm9713_codec;
		break;
#endif
	default:
		dev_err(wm->dev, "Support for wm97%02x not compiled in.\n",
			wm->id & 0xff);
		ret = -ENODEV;
		goto alloc_err;
	}
