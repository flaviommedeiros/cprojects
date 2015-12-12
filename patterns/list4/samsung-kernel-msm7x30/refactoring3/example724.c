switch (reg) {
	case 0: asm("movdqu %0, %%xmm0" : : "m"(*data)); break;
	case 1: asm("movdqu %0, %%xmm1" : : "m"(*data)); break;
	case 2: asm("movdqu %0, %%xmm2" : : "m"(*data)); break;
	case 3: asm("movdqu %0, %%xmm3" : : "m"(*data)); break;
	case 4: asm("movdqu %0, %%xmm4" : : "m"(*data)); break;
	case 5: asm("movdqu %0, %%xmm5" : : "m"(*data)); break;
	case 6: asm("movdqu %0, %%xmm6" : : "m"(*data)); break;
	case 7: asm("movdqu %0, %%xmm7" : : "m"(*data)); break;
#ifdef CONFIG_X86_64
	case 8: asm("movdqu %0, %%xmm8" : : "m"(*data)); break;
	case 9: asm("movdqu %0, %%xmm9" : : "m"(*data)); break;
	case 10: asm("movdqu %0, %%xmm10" : : "m"(*data)); break;
	case 11: asm("movdqu %0, %%xmm11" : : "m"(*data)); break;
	case 12: asm("movdqu %0, %%xmm12" : : "m"(*data)); break;
	case 13: asm("movdqu %0, %%xmm13" : : "m"(*data)); break;
	case 14: asm("movdqu %0, %%xmm14" : : "m"(*data)); break;
	case 15: asm("movdqu %0, %%xmm15" : : "m"(*data)); break;
#endif
	default: BUG();
	}
