if (pfile_in_zip_read_info->stream_initialised == Z_DEFLATED)
	{
		inflateEnd(&pfile_in_zip_read_info->stream);
	}
#ifdef HAVE_BZIP2
	else if (pfile_in_zip_read_info->stream_initialised == Z_BZIP2ED)
	{
		BZ2_bzDecompressEnd(&pfile_in_zip_read_info->bstream);
	}
#endif
