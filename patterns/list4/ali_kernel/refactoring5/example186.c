#ifdef CONFIG_FB_MATROX_G
if (minfo->devflags.g450dac) {
		minfo->outputs[0].output = &g450out;
	} else
#endif
	{
		minfo->outputs[0].output = &m1064;
	}
