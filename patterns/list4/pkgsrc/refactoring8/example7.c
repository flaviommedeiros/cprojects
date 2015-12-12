static const char * const suffixes[] = {
	"",	/* 2^0  (byte) */
	"KiB",	/* 2^10 Kibibyte */
	"MiB",	/* 2^20 Mebibyte */
	"GiB",	/* 2^30 Gibibyte */
	"TiB",	/* 2^40 Tebibyte */
	"PiB",	/* 2^50 Pebibyte */
	"EiB",	/* 2^60 Exbibyte */
#if 0
		/* The following are not necessary for signed 64-bit off_t */
	"ZiB",	/* 2^70 Zebibyte */
	"YiB",	/* 2^80 Yobibyte */
#endif
};
