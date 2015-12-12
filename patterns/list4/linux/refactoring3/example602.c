switch (data->clock_mode) {
#ifdef CONFIG_CSRC_R4K
	case VDSO_CLOCK_R4K:
		cycle_now = read_r4k_count();
		break;
#endif
#ifdef CONFIG_CLKSRC_MIPS_GIC
	case VDSO_CLOCK_GIC:
		cycle_now = read_gic_count(data);
		break;
#endif
	default:
		return 0;
	}
