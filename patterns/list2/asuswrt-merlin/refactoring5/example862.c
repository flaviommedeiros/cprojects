#ifdef CONFIG_FB_MATROX_G
if (ACCESS_FBINFO(devflags.g450dac)) {
		ACCESS_FBINFO(outputs[0]).output = &g450out;
	} else
#endif
	{
		ACCESS_FBINFO(outputs[0]).output = &m1064;
	}
