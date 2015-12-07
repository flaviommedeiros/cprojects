#ifdef _MSC_VER
if(f == stdin) {
		/* MS' stdio impl can't even seek forward on stdin, have to use pure non-fseek() version: */
		while(offset > 0) {
			const long need = (long)min(offset, sizeof(dump));
			if((long)fread(dump, 1, need, f) < need)
				return false;
			offset -= need;
		}
	}
	else
#endif
	{
		while(offset > 0) {
			long need = (long)min(offset, LONG_MAX);
			if(fseeko(f, need, SEEK_CUR) < 0) {
				need = (long)min(offset, sizeof(dump));
				if((long)fread(dump, 1, need, f) < need)
					return false;
			}
			offset -= need;
		}
	}
