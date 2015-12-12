#ifndef _WIN32
if(strlen(comport) == 0) {
		gpio_initpgm(*pgm);
		(*pgm)->pinno[3] = FIRMWARE_GPIO_RESET;
		(*pgm)->pinno[4] = FIRMWARE_GPIO_SCK;
		(*pgm)->pinno[5] = FIRMWARE_GPIO_MOSI;
		(*pgm)->pinno[6] = FIRMWARE_GPIO_MISO;
		// (*pgm)->ispdelay = 50;

		settings_find_number("firmware-gpio-reset", (int *)&(*pgm)->pinno[3]);
		settings_find_number("firmware-gpio-sck", (int *)&(*pgm)->pinno[4]);
		settings_find_number("firmware-gpio-mosi", (int *)&(*pgm)->pinno[5]);
		settings_find_number("firmware-gpio-miso", (int *)&(*pgm)->pinno[6]);
	} else {
#endif
		arduino_initpgm(*pgm);
#ifdef _WIN32
		(*pgm)->baudrate = 57600;
#else
		(*pgm)->baudrate = B57600;
	}
