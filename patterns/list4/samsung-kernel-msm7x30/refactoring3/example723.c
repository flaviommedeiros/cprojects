switch (reg) {
	case 0: asm("movdqu %%xmm0, %0" : "=m"(*data)); break;
	case 1: asm("movdqu %%xmm1, %0" : "=m"(*data)); break;
	case 2: asm("movdqu %%xmm2, %0" : "=m"(*data)); break;
	case 3: asm("movdqu %%xmm3, %0" : "=m"(*data)); break;
	case 4: asm("movdqu %%xmm4, %0" : "=m"(*data)); break;
	case 5: asm("movdqu %%xmm5, %0" : "=m"(*data)); break;
	case 6: asm("movdqu %%xmm6, %0" : "=m"(*data)); break;
	case 7: asm("movdqu %%xmm7, %0" : "=m"(*data)); break;
#ifdef CONFIG_X86_64
	case 8: asm("movdqu %%xmm8, %0" : "=m"(*data)); break;
	case 9: asm("movdqu %%xmm9, %0" : "=m"(*data)); break;
	case 10: asm("movdqu %%xmm10, %0" : "=m"(*data)); break;
	case 11: asm("movdqu %%xmm11, %0" : "=m"(*data)); break;
	case 12: asm("movdqu %%xmm12, %0" : "=m"(*data)); break;
	case 13: asm("movdqu %%xmm13, %0" : "=m"(*data)); break;
	case 14: asm("movdqu %%xmm14, %0" : "=m"(*data)); break;
	case 15: asm("movdqu %%xmm15, %0" : "=m"(*data)); break;
#endif
	default: BUG();
	}
