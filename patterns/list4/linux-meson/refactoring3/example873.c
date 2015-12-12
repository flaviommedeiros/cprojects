switch (get_clk_type(clk_id)) {
	case IVA2_CLK:
		clk_disable(iva2_clk);
		break;
	case GPT_CLK:
		status = omap_dm_timer_stop(timer[clk_id - 1]);
		break;
#ifdef CONFIG_OMAP_MCBSP
	case MCBSP_CLK:
		omap2_mcbsp_set_clks_src(MCBSP_ID(clk_id), MCBSP_CLKS_PRCM_SRC);
		omap_mcbsp_free(MCBSP_ID(clk_id));
		break;
#endif
	case WDT_CLK:
		dev_err(bridge, "ERROR: DSP requested to disable WDT3 clk\n");
		break;
	case SSI_CLK:
		ssi_clk_prepare(false);
		ssi_clk_prepare(false);
		clk_disable(ssi.sst_fck);
		clk_disable(ssi.ssr_fck);
		clk_disable(ssi.ick);
		break;
	default:
		dev_err(bridge, "Invalid clock id for disable\n");
		status = -EPERM;
	}
