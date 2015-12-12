if (tif->tif_header.common.tiff_magic != TIFF_BIGENDIAN &&
	    tif->tif_header.common.tiff_magic != TIFF_LITTLEENDIAN
	    #if MDI_SUPPORT
	    &&
	    #if HOST_BIGENDIAN
	    tif->tif_header.common.tiff_magic != MDI_BIGENDIAN
	    #else
	    tif->tif_header.common.tiff_magic != MDI_LITTLEENDIAN
	    #endif
	    ) {
		TIFFErrorExt(tif->tif_clientdata, name,
		    "Not a TIFF or MDI file, bad magic number %d (0x%x)",
	    #else
	    ) {
		TIFFErrorExt(tif->tif_clientdata, name,
		    "Not a TIFF file, bad magic number %d (0x%x)",
	    #endif
		    tif->tif_header.common.tiff_magic,
		    tif->tif_header.common.tiff_magic);
		goto bad;
	}
