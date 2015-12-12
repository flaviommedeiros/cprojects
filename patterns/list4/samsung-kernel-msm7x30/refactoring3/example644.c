switch (idx) {
	case 1:
		val = mfspr(SPRN_PMC1);
		break;
	case 2:
		val = mfspr(SPRN_PMC2);
		break;
	case 3:
		val = mfspr(SPRN_PMC3);
		break;
	case 4:
		val = mfspr(SPRN_PMC4);
		break;
	case 5:
		val = mfspr(SPRN_PMC5);
		break;
	case 6:
		val = mfspr(SPRN_PMC6);
		break;
#ifdef CONFIG_PPC64
	case 7:
		val = mfspr(SPRN_PMC7);
		break;
	case 8:
		val = mfspr(SPRN_PMC8);
		break;
#endif /* CONFIG_PPC64 */
	default:
		printk(KERN_ERR "oops trying to read PMC%d\n", idx);
		val = 0;
	}
