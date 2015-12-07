#ifdef MIKMOD_DEBUG
if (eff>=0x10)
		fprintf(stderr,"UniPTEffect called with incorrect eff value %d\n",eff);
	else
#endif
	if((eff)||(dat)||(of.flags & UF_ARPMEM)) UniEffect(UNI_PTEFFECT0+eff,dat);
