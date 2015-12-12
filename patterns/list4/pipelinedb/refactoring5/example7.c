#ifdef HAVE_LIBZ
if (compression != 0)
	{
		char		fmode[10];

		/* Don't use PG_BINARY_x since this is zlib */
		sprintf(fmode, "wb%d", compression);
		if (fn >= 0)
			AH->OF = gzdopen(dup(fn), fmode);
		else
			AH->OF = gzopen(filename, fmode);
		AH->gzOut = 1;
	}
	else
#endif
	{							/* Use fopen */
		if (AH->mode == archModeAppend)
		{
			if (fn >= 0)
				AH->OF = fdopen(dup(fn), PG_BINARY_A);
			else
				AH->OF = fopen(filename, PG_BINARY_A);
		}
		else
		{
			if (fn >= 0)
				AH->OF = fdopen(dup(fn), PG_BINARY_W);
			else
				AH->OF = fopen(filename, PG_BINARY_W);
		}
		AH->gzOut = 0;
	}
