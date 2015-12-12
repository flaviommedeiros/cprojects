#ifdef JPEG_LIB_MK1
if (td->td_bitspersample != 8 && td->td_bitspersample != 12) 
#else
	if (td->td_bitspersample != BITS_IN_JSAMPLE )
#endif
	{
		TIFFErrorExt(tif->tif_clientdata, module, "BitsPerSample %d not allowed for JPEG",
			  (int) td->td_bitspersample);
		return (0);
	}
