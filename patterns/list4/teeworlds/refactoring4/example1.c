#if USE_ZLIB
if(inflateEnd(stream) != Z_OK)
#else
	if(z_inflateEnd(stream) != Z_OK)
#endif
	{
		printf("ZLIB says: %s\n", stream->msg);
		return PNG_ZLIB_ERROR;
	}
