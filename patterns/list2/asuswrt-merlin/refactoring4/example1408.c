#ifndef CONFIG_IDEDMA_IVB
if (id->hw_config & 0x4000)
#else
	if (id->hw_config & 0x6000)
#endif
		return 1;
