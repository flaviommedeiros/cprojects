int dsp_clk_enable(enum dsp_clk_id clk_id)
{
	int status = 0;

	if (is_dsp_clk_active(dsp_clocks, clk_id)) {
		dev_err(bridge, "WARN: clock id %d already enabled\n", clk_id);
		goto out;
	}

	switch (get_clk_type(clk_id)) {
	case IVA2_CLK:
		clk_enable(iva2_clk);
		break;
	case GPT_CLK:
		status = omap_dm_timer_start(timer[clk_id - 1]);
		break;
#ifdef CONFIG_OMAP_MCBSP
	case MCBSP_CLK:
		omap_mcbsp_request(MCBSP_ID(clk_id));
		omap2_mcbsp_set_clks_src(MCBSP_ID(clk_id), MCBSP_CLKS_PAD_SRC);
		break;
#endif
	case WDT_CLK:
		dev_err(bridge, "ERROR: DSP requested to enable WDT3 clk\n");
		break;
	case SSI_CLK:
		clk_enable(ssi.sst_fck);
		clk_enable(ssi.ssr_fck);
		clk_enable(ssi.ick);

		/*
		 * The SSI module need to configured not to have the Forced
		 * idle for master interface. If it is set to forced idle,
		 * the SSI module is transitioning to standby thereby causing
		 * the client in the DSP hang waiting for the SSI module to
		 * be active after enabling the clocks
		 */
		ssi_clk_prepare(true);
		break;
	default:
		dev_err(bridge, "Invalid clock id for enable\n");
		status = -EPERM;
	}

	if (!status)
		set_dsp_clk_active(&dsp_clocks, clk_id);

out:
	return status;
}
