if( (!ivideo->sisvga_enabled)
#if !defined(__i386__) && !defined(__x86_64__)
			      || (sisfb_resetcard)
#endif
						   ) {
		for(i = 0x30; i <= 0x3f; i++) {
			SiS_SetReg(SISCR, i, 0x00);
		}
	}
