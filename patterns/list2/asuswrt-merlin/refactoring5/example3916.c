#ifndef ASSABET_PAL_VIDEO
if (on) {
		ASSABET_BCR_set(ASSABET_BCR_LCD_ON);
		udelay(500);
	} else
#endif
		ASSABET_BCR_clear(ASSABET_BCR_LCD_ON);
