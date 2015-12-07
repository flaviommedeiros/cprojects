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
