#ifdef ARCH_ARM
if (accel & MPEG2_ACCEL_ARM) {
	mpeg2_mc = mpeg2_mc_arm;
    } else
#endif
	mpeg2_mc = mpeg2_mc_c;
