switch ((aml_read_reg32(P_HHI_VPU_CLK_CNTL) >> 9) & 0x7) {
		case 0:
			clk_source = 637500000;
			break;
		case 1:
			clk_source = 850000000;
			break;
		case 2:
			clk_source = 510000000;
			break;
		case 3:
			clk_source = 364300000;
			break;
#ifdef GP1_CLK_TEST
		case 7:
			clk_source = 696000000;
			break;
#endif
		default:
			clk_source = 0;
			break;
	}
