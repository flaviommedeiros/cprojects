switch (clk_type) {
#ifdef CONFIG_ATARI
		case CLK_ATI18818_1:
			par->pll_ops = &aty_pll_ati18818_1;
			break;
#else
		case CLK_IBMRGB514:
			par->pll_ops = &aty_pll_ibm514;
			break;
#endif
#if 0 /* dead code */
		case CLK_STG1703:
			par->pll_ops = &aty_pll_stg1703;
			break;
		case CLK_CH8398:
			par->pll_ops = &aty_pll_ch8398;
			break;
		case CLK_ATT20C408:
			par->pll_ops = &aty_pll_att20c408;
			break;
#endif
		default:
			PRINTKI("aty_init: CLK type not implemented yet!");
			par->pll_ops = &aty_pll_unsupported;
			break;
		}
