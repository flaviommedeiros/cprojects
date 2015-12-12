#if LZ4_ARCH64
if ((ref + COPYLENGTH) > oend)
#else
			if ((ref + COPYLENGTH) > oend ||
					(op + COPYLENGTH) > oend)
#endif
				goto _output_error;
