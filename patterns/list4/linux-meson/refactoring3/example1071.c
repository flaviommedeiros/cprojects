switch (c->x86) {
#ifdef CONFIG_X86_32
	case 5:
		/* Emulate MTRRs using Centaur's MCR. */
		set_cpu_cap(c, X86_FEATURE_CENTAUR_MCR);
		break;
#endif
	case 6:
		if (c->x86_model >= 0xf)
			set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		break;
	}
