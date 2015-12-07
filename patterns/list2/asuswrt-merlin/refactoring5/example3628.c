#ifdef CONFIG_MTD_NFLASH
if ((sih->ccrev == 38) && ((sih->chipst & (1 << 4)) != 0)) {
			fltype = NFLASH;
			base = KSEG1ADDR(SI_FLASH1);
		} else
#endif
		{
			fltype = readl(&cc->capabilities) & CC_CAP_FLASH_MASK;
			base = KSEG1ADDR(SI_FLASH2);
		}
