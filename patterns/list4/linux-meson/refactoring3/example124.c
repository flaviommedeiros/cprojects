switch (device) {
#ifdef CONFIG_VT
	case MKDEV(TTY_MAJOR, 0): {
		extern struct tty_driver *console_driver;
		driver = tty_driver_kref_get(console_driver);
		*index = fg_console;
		*noctty = 1;
		break;
	}
#endif
	case MKDEV(TTYAUX_MAJOR, 1): {
		struct tty_driver *console_driver = console_device(index);
		if (console_driver) {
			driver = tty_driver_kref_get(console_driver);
			if (driver) {
				/* Don't let /dev/console block */
				filp->f_flags |= O_NONBLOCK;
				*noctty = 1;
				break;
			}
		}
		return ERR_PTR(-ENODEV);
	}
	default:
		driver = get_tty_driver(device, index);
		if (!driver)
			return ERR_PTR(-ENODEV);
		break;
	}
