#ifdef RTCONFIG_MMC_LED
if(*nvram_safe_get("usb_path3"))
		fake_dev_led(nvram_safe_get("mmc_irq"), LED_MMC);
