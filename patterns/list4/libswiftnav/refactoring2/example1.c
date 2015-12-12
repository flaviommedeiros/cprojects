#ifndef NO_LONG_LONG
if (sizeof(long long) < 8)
#endif
			fprintf(f, "#define NO_LONG_LONG\n");
