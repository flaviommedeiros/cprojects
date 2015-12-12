switch (pdrv) {
	case FLASH :
#endif
		// ?
		return RES_OK;
#ifdef CFG_HAVE_SD
	case SD :
		result = MMC_disk_status();
		// translate the reslut code here
		return stat;
	}
