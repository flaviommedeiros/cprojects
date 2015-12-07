#ifdef ARCH_X86
if (accel & MPEG2_ACCEL_X86_SSE2) {
	mpeg2_idct_copy = mpeg2_idct_copy_sse2;
	mpeg2_idct_add = mpeg2_idct_add_sse2;
	mpeg2_idct_mmx_init ();
    } else if (accel & MPEG2_ACCEL_X86_MMXEXT) {
	mpeg2_idct_copy = mpeg2_idct_copy_mmxext;
	mpeg2_idct_add = mpeg2_idct_add_mmxext;
	mpeg2_idct_mmx_init ();
    } else if (accel & MPEG2_ACCEL_X86_MMX) {
	mpeg2_idct_copy = mpeg2_idct_copy_mmx;
	mpeg2_idct_add = mpeg2_idct_add_mmx;
	mpeg2_idct_mmx_init ();
    } else
#endif
#ifdef ARCH_PPC
    if (accel & MPEG2_ACCEL_PPC_ALTIVEC) {
	mpeg2_idct_copy = mpeg2_idct_copy_altivec;
	mpeg2_idct_add = mpeg2_idct_add_altivec;
	mpeg2_idct_altivec_init ();
    } else
#endif
#ifdef ARCH_ALPHA
    if (accel & MPEG2_ACCEL_ALPHA_MVI) {
	mpeg2_idct_copy = mpeg2_idct_copy_mvi;
	mpeg2_idct_add = mpeg2_idct_add_mvi;
	mpeg2_idct_alpha_init ();
    } else if (accel & MPEG2_ACCEL_ALPHA) {
	int i;

	mpeg2_idct_copy = mpeg2_idct_copy_alpha;
	mpeg2_idct_add = mpeg2_idct_add_alpha;
	mpeg2_idct_alpha_init ();
	for (i = -3840; i < 3840 + 256; i++)
	    CLIP(i) = (i < 0) ? 0 : ((i > 255) ? 255 : i);
    } else
#endif
    {
	int i, j;

	mpeg2_idct_copy = mpeg2_idct_copy_c;
	mpeg2_idct_add = mpeg2_idct_add_c;
	for (i = -3840; i < 3840 + 256; i++)
	    CLIP(i) = (i < 0) ? 0 : ((i > 255) ? 255 : i);
	for (i = 0; i < 64; i++) {
	    j = mpeg2_scan_norm[i];
	    mpeg2_scan_norm[i] = ((j & 0x36) >> 1) | ((j & 0x09) << 2);
	    j = mpeg2_scan_alt[i];
	    mpeg2_scan_alt[i] = ((j & 0x36) >> 1) | ((j & 0x09) << 2);
	}
    }
