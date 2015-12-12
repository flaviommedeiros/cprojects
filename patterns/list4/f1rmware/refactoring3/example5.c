switch (pdrv) {
	case FLASH :
#endif
		flash_read(FLASHFS_OFFSET+sector*512,count*512,buff);
		return RES_OK;

#ifdef CFG_HAVE_SD
	case SD :
		// translate the arguments here

		result = MMC_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
#endif

	return RES_PARERR;
}
