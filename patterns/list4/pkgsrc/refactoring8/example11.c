FSUB fsub[] = {
#ifndef NO_CPIO
/* 0: OLD BINARY CPIO */
	{ "bcpio", 5120, sizeof(HD_BCPIO), 1, 0, 0, 1, bcpio_id, cpio_strd,
	bcpio_rd, bcpio_endrd, cpio_stwr, bcpio_wr, cpio_endwr, NULL,
	cpio_subtrail, rd_wrfile, wr_rdfile, bad_opt },

/* 1: OLD OCTAL CHARACTER CPIO */
	{ "cpio", 5120, sizeof(HD_CPIO), 1, 0, 0, 1, cpio_id, cpio_strd,
	cpio_rd, cpio_endrd, cpio_stwr, cpio_wr, cpio_endwr, NULL,
	cpio_subtrail, rd_wrfile, wr_rdfile, bad_opt },

/* 2: SVR4 HEX CPIO */
	{ "sv4cpio", 5120, sizeof(HD_VCPIO), 1, 0, 0, 1, vcpio_id, cpio_strd,
	vcpio_rd, vcpio_endrd, cpio_stwr, vcpio_wr, cpio_endwr, NULL,
	cpio_subtrail, rd_wrfile, wr_rdfile, bad_opt },

/* 3: SVR4 HEX CPIO WITH CRC */
	{ "sv4crc", 5120, sizeof(HD_VCPIO), 1, 0, 0, 1, crc_id, crc_strd,
	vcpio_rd, vcpio_endrd, crc_stwr, vcpio_wr, cpio_endwr, NULL,
	cpio_subtrail, rd_wrfile, wr_rdfile, bad_opt },
#endif
/* 4: OLD TAR */
	{ "tar", 10240, BLKMULT, 0, 1, BLKMULT, 0, tar_id, no_op,
	tar_rd, tar_endrd, no_op, tar_wr, tar_endwr, tar_trail,
	NULL, rd_wrfile, wr_rdfile, tar_opt },

/* 5: POSIX USTAR */
	{ "ustar", 10240, BLKMULT, 0, 1, BLKMULT, 0, ustar_id, ustar_strd,
	ustar_rd, tar_endrd, ustar_stwr, ustar_wr, tar_endwr, tar_trail,
	NULL, rd_wrfile, wr_rdfile, bad_opt }
};
