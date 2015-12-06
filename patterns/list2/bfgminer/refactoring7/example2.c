return
#ifdef USE_VFIO
		lpi_vfio.open(path, barcfgs) ?:
#endif
#ifdef USE_UIO
		lpi_uio.open(path, barcfgs) ?:
#endif
		false;
