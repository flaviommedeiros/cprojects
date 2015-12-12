#ifdef HDIO_GETGEO
if (cxt->geom.heads && cxt->geom.sectors) {
		fdisk_sector_t llsectors;

		if (blkdev_get_sectors(cxt->dev_fd, (unsigned long long *) &llsectors) == 0) {
			int sec_fac = cxt->sector_size / 512;
			fdisk_sector_t llcyls;

			llcyls = llsectors / (cxt->geom.heads * cxt->geom.sectors * sec_fac);
			cxt->geom.cylinders = llcyls;
			if (cxt->geom.cylinders != llcyls)
				cxt->geom.cylinders = ~0;
		} else {
			fdisk_warnx(cxt,
				_("BLKGETSIZE ioctl failed on %s. "
				  "Using geometry cylinder value of %llu. "
				  "This value may be truncated for devices "
				  "> 33.8 GB."),
				cxt->dev_path, cxt->geom.cylinders);
		}
	} else
#endif
		ask_geom(cxt);
