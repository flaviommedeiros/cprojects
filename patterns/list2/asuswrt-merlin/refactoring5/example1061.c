#ifdef	CFG_ZLIB
if (memcmp(c, "\x1f\x8b", 2) == 0)
			zh = "z";
		else
#endif
#ifdef	CFG_LZMA
		if (memcmp(c, "\x5d\x00", 2) == 0)
			zh = "lzma";
		else
#endif
		{
			xprintf("Image compressed with unsupported method\n");
			res = CFE_ERR_UNSUPPORTED;
			goto errout;
		}
