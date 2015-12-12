#ifdef CONFIG_MACH_ARIESVE
if(FGAdjustSOC%100 >= 50)
#else
	if(FGAdjustSOC%100 >= 50 && FGSOC > 1)
#endif
		FGSOC+=1;
