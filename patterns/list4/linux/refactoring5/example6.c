#ifdef CONFIG_PXA3xx
if (cpu_is_pxa3xx())
		pxa_ac97_warm_pxa3xx();
	else
#endif
		snd_BUG();
