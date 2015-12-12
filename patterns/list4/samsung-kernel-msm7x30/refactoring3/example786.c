switch ((product_id >> 8) & 0xff) {
#ifdef CONFIG_ARCH_IXP2000
	case 0:		/* IXP2800 */
		if (!(c->cpu_model_bitmask & 4))
			return 0;
		break;

	case 1:		/* IXP2850 */
		if (!(c->cpu_model_bitmask & 8))
			return 0;
		break;

	case 2:		/* IXP2400 */
		if (!(c->cpu_model_bitmask & 2))
			return 0;
		break;
#endif

#ifdef CONFIG_ARCH_IXP23XX
	case 4:		/* IXP23xx */
		if (!(c->cpu_model_bitmask & 0x3f0))
			return 0;
		break;
#endif

	default:
		return 0;
	}
