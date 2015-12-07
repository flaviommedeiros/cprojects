#ifdef ARCH_PPC
if (accel & MPEG2_ACCEL_PPC_ALTIVEC)
	mpeg2_mc = mpeg2_mc_altivec;
    else
#endif
#ifdef ARCH_ALPHA
    if (accel & MPEG2_ACCEL_ALPHA)
	mpeg2_mc = mpeg2_mc_alpha;
    else
#endif
#ifdef ARCH_SPARC
    if (accel & MPEG2_ACCEL_SPARC_VIS)
	mpeg2_mc = mpeg2_mc_vis;
    else
#endif
#ifdef ARCH_ARM
    if (accel & MPEG2_ACCEL_ARM) {
	mpeg2_mc = mpeg2_mc_arm;
    } else
#endif
	mpeg2_mc = mpeg2_mc_c;
