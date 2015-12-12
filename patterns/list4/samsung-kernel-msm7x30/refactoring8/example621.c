static inline u32 __pure crc32_be_generic(u32 crc, unsigned char const *p,
					  size_t len, const u32 (*tab)[256],
					  u32 polynomial)
{
#if CRC_BE_BITS == 1
	int i;
	while (len--) {
		crc ^= *p++ << 24;
		for (i = 0; i < 8; i++)
			crc =
			    (crc << 1) ^ ((crc & 0x80000000) ? polynomial :
					  0);
	}
# elif CRC_BE_BITS == 2
	while (len--) {
		crc ^= *p++ << 24;
		crc = (crc << 2) ^ tab[0][crc >> 30];
		crc = (crc << 2) ^ tab[0][crc >> 30];
		crc = (crc << 2) ^ tab[0][crc >> 30];
		crc = (crc << 2) ^ tab[0][crc >> 30];
	}
# elif CRC_BE_BITS == 4
	while (len--) {
		crc ^= *p++ << 24;
		crc = (crc << 4) ^ tab[0][crc >> 28];
		crc = (crc << 4) ^ tab[0][crc >> 28];
	}
# elif CRC_BE_BITS == 8
	while (len--) {
		crc ^= *p++ << 24;
		crc = (crc << 8) ^ tab[0][crc >> 24];
	}
# else
	crc = (__force u32) __cpu_to_be32(crc);
	crc = crc32_body(crc, p, len, tab);
	crc = __be32_to_cpu((__force __be32)crc);
# endif
	return crc;
}
