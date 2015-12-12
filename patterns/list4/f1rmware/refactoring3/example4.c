switch (pdrv) {
	case FLASH :
#endif
		flashInit();
		return RES_OK;

#ifdef CFG_HAVE_SD
	case SD :
		result = MMC_disk_initialize();

		// translate the reslut code here

		return stat;
	}
