switch (pdrv) {
	case FLASH :
#endif

		// Process of the command for the ATA drive
		if(cmd==CTRL_SYNC)
			res=RES_OK;
		return res;

#ifdef CFG_HAVE_SD
	case SD :
		// Process of the command for the MMC/SD card
		return res;
	}
