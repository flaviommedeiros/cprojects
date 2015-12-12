switch (reg) {
	case 0: asm("movdqa %%xmm0, %0" : "=m"(*data)); break;
	case 1: asm("movdqa %%xmm1, %0" : "=m"(*data)); break;
	case 2: asm("movdqa %%xmm2, %0" : "=m"(*data)); break;
	case 3: asm("movdqa %%xmm3, %0" : "=m"(*data)); break;
	case 4: asm("movdqa %%xmm4, %0" : "=m"(*data)); break;
	case 5: asm("movdqa %%xmm5, %0" : "=m"(*data)); break;
	case 6: asm("movdqa %%xmm6, %0" : "=m"(*data)); break;
	case 7: asm("movdqa %%xmm7, %0" : "=m"(*data)); break;
#ifdef CONFIG_X86_64
	case 8: asm("movdqa %%xmm8, %0" : "=m"(*data)); break;
	case 9: asm("movdqa %%xmm9, %0" : "=m"(*data)); break;
	case 10: asm("movdqa %%xmm10, %0" : "=m"(*data)); break;
	case 11: asm("movdqa %%xmm11, %0" : "=m"(*data)); break;
	case 12: asm("movdqa %%xmm12, %0" : "=m"(*data)); break;
	case 13: asm("movdqa %%xmm13, %0" : "=m"(*data)); break;
	case 14: asm("movdqa %%xmm14, %0" : "=m"(*data)); break;
	case 15: asm("movdqa %%xmm15, %0" : "=m"(*data)); break;
#endif
	default: BUG();
	}
