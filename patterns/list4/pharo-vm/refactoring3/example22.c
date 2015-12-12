switch (lcd_dev->mod) {
#ifdef GTK_LCD
		case LCD_MOD_GTK:
			ret = gtk_lcd_init(lcd_dev);
			break;
#endif
#ifdef WIN32_LCD
		case LCD_MOD_WIN32:
			ret = win32_lcd_init(lcd_dev);
			break;
#endif
#ifdef BEOS_LCD
		case LCD_MOD_BEOS:
			ret = beos_lcd_init(lcd_dev);
			break;
#endif
		default:
			ret = -1;
			break;
	}
