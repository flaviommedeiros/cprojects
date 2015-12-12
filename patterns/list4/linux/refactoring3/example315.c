switch (dac_subtype) {
		case DAC_IBMRGB514:
			par->dac_ops = &aty_dac_ibm514;
			break;
#ifdef CONFIG_ATARI
		case DAC_ATI68860_B:
		case DAC_ATI68860_C:
			par->dac_ops = &aty_dac_ati68860b;
			break;
		case DAC_ATT20C408:
		case DAC_ATT21C498:
			par->dac_ops = &aty_dac_att21c498;
			break;
#endif
		default:
			PRINTKI("aty_init: DAC type not implemented yet!\n");
			par->dac_ops = &aty_dac_unsupported;
			break;
		}
