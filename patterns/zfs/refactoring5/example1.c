#ifdef HAVE_UIO_ZEROCOPY
if ((uio->uio_extflg == UIO_XUIO) &&
	    (((xuio_t *)uio)->xu_type == UIOTYPE_ZEROCOPY))
		xuio = (xuio_t *)uio;
	else
#endif
		uio_prefaultpages(MIN(n, max_blksz), uio);
