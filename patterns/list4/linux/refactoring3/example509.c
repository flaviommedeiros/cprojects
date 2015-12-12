switch (c->x86) {
#ifdef CONFIG_X86_32
	case 5:
		switch (c->x86_model) {
		case 4:
			name = "C6";
			fcr_set = ECX8|DSMC|EDCTLB|EMMX|ERETSTK;
			fcr_clr = DPDC;
			printk(KERN_NOTICE "Disabling bugged TSC.\n");
			clear_cpu_cap(c, X86_FEATURE_TSC);
			break;
		case 8:
			switch (c->x86_mask) {
			default:
			name = "2";
				break;
			case 7 ... 9:
				name = "2A";
				break;
			case 10 ... 15:
				name = "2B";
				break;
			}
			fcr_set = ECX8|DSMC|DTLOCK|EMMX|EBRPRED|ERETSTK|
				  E2MMX|EAMD3D;
			fcr_clr = DPDC;
			break;
		case 9:
			name = "3";
			fcr_set = ECX8|DSMC|DTLOCK|EMMX|EBRPRED|ERETSTK|
				  E2MMX|EAMD3D;
			fcr_clr = DPDC;
			break;
		default:
			name = "??";
		}

		rdmsr(MSR_IDT_FCR1, lo, hi);
		newlo = (lo|fcr_set) & (~fcr_clr);

		if (newlo != lo) {
			printk(KERN_INFO "Centaur FCR was 0x%X now 0x%X\n",
				lo, newlo);
			wrmsr(MSR_IDT_FCR1, newlo, hi);
		} else {
			printk(KERN_INFO "Centaur FCR is 0x%X\n", lo);
		}
		/* Emulate MTRRs using Centaur's MCR. */
		set_cpu_cap(c, X86_FEATURE_CENTAUR_MCR);
		/* Report CX8 */
		set_cpu_cap(c, X86_FEATURE_CX8);
		/* Set 3DNow! on Winchip 2 and above. */
		if (c->x86_model >= 8)
			set_cpu_cap(c, X86_FEATURE_3DNOW);
		/* See if we can find out some more. */
		if (cpuid_eax(0x80000000) >= 0x80000005) {
			/* Yes, we can. */
			cpuid(0x80000005, &aa, &bb, &cc, &dd);
			/* Add L1 data and code cache sizes. */
			c->x86_cache_size = (cc>>24)+(dd>>24);
		}
		sprintf(c->x86_model_id, "WinChip %s", name);
		break;
#endif
	case 6:
		init_c3(c);
		break;
	}
