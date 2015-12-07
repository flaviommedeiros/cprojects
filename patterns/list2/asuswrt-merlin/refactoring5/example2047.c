#ifdef XZ_DEC_BCJ
if (s->bcj_active)
		ret = xz_dec_bcj_run(s->bcj, s->lzma2, b);
	else
#endif
		ret = xz_dec_lzma2_run(s->lzma2, b);
