switch (cmd) {
#ifdef __sparc__
	case FBIOGTYPE:
		fbtyp.fb_type = FBTYPE_PCI_GENERIC;
		fbtyp.fb_width = par->crtc.vxres;
		fbtyp.fb_height = par->crtc.vyres;
		fbtyp.fb_depth = info->var.bits_per_pixel;
		fbtyp.fb_cmsize = info->cmap.len;
		fbtyp.fb_size = info->fix.smem_len;
		if (copy_to_user((struct fbtype __user *) arg, &fbtyp,
				 sizeof(fbtyp)))
			return -EFAULT;
		break;
#endif /* __sparc__ */

	case FBIO_WAITFORVSYNC:
		{
			u32 crtc;

			if (get_user(crtc, (__u32 __user *) arg))
				return -EFAULT;

			return aty_waitforvblank(par, crtc);
		}
		break;

#if defined(DEBUG) && defined(CONFIG_FB_ATY_CT)
	case ATYIO_CLKR:
		if (M64_HAS(INTEGRATED)) {
			struct atyclk clk;
			union aty_pll *pll = &par->pll;
			u32 dsp_config = pll->ct.dsp_config;
			u32 dsp_on_off = pll->ct.dsp_on_off;
			clk.ref_clk_per = par->ref_clk_per;
			clk.pll_ref_div = pll->ct.pll_ref_div;
			clk.mclk_fb_div = pll->ct.mclk_fb_div;
			clk.mclk_post_div = pll->ct.mclk_post_div_real;
			clk.mclk_fb_mult = pll->ct.mclk_fb_mult;
			clk.xclk_post_div = pll->ct.xclk_post_div_real;
			clk.vclk_fb_div = pll->ct.vclk_fb_div;
			clk.vclk_post_div = pll->ct.vclk_post_div_real;
			clk.dsp_xclks_per_row = dsp_config & 0x3fff;
			clk.dsp_loop_latency = (dsp_config >> 16) & 0xf;
			clk.dsp_precision = (dsp_config >> 20) & 7;
			clk.dsp_off = dsp_on_off & 0x7ff;
			clk.dsp_on = (dsp_on_off >> 16) & 0x7ff;
			if (copy_to_user((struct atyclk __user *) arg, &clk,
					 sizeof(clk)))
				return -EFAULT;
		} else
			return -EINVAL;
		break;
	case ATYIO_CLKW:
		if (M64_HAS(INTEGRATED)) {
			struct atyclk clk;
			union aty_pll *pll = &par->pll;
			if (copy_from_user(&clk, (struct atyclk __user *) arg,
					   sizeof(clk)))
				return -EFAULT;
			par->ref_clk_per = clk.ref_clk_per;
			pll->ct.pll_ref_div = clk.pll_ref_div;
			pll->ct.mclk_fb_div = clk.mclk_fb_div;
			pll->ct.mclk_post_div_real = clk.mclk_post_div;
			pll->ct.mclk_fb_mult = clk.mclk_fb_mult;
			pll->ct.xclk_post_div_real = clk.xclk_post_div;
			pll->ct.vclk_fb_div = clk.vclk_fb_div;
			pll->ct.vclk_post_div_real = clk.vclk_post_div;
			pll->ct.dsp_config = (clk.dsp_xclks_per_row & 0x3fff) |
				((clk.dsp_loop_latency & 0xf) << 16) |
				((clk.dsp_precision & 7) << 20);
			pll->ct.dsp_on_off = (clk.dsp_off & 0x7ff) |
				((clk.dsp_on & 0x7ff) << 16);
			/*aty_calc_pll_ct(info, &pll->ct);*/
			aty_set_pll_ct(info, pll);
		} else
			return -EINVAL;
		break;
	case ATYIO_FEATR:
		if (get_user(par->features, (u32 __user *) arg))
			return -EFAULT;
		break;
	case ATYIO_FEATW:
		if (put_user(par->features, (u32 __user *) arg))
			return -EFAULT;
		break;
#endif /* DEBUG && CONFIG_FB_ATY_CT */
	default:
		return -EINVAL;
	}
