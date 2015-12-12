switch (mfd->panel.type) {
	case EXT_MDDI_PANEL:
	case MDDI_PANEL:
	case EBI2_PANEL:
		INIT_WORK(&mfd->dma_update_worker,
			  mdp_lcd_update_workqueue_handler);
		INIT_WORK(&mfd->vsync_resync_worker,
			  mdp_vsync_resync_workqueue_handler);
		mfd->hw_refresh = FALSE;

		if (mfd->panel.type == EXT_MDDI_PANEL) {
			/* 15 fps -> 66 msec */
			mfd->refresh_timer_duration = (66 * HZ / 1000);
		} else {
			/* 24 fps -> 42 msec */
			mfd->refresh_timer_duration = (42 * HZ / 1000);
		}

#ifdef CONFIG_FB_MSM_MDP22
		mfd->dma_fnc = mdp_dma2_update;
		mfd->dma = &dma2_data;
#else
		if (mfd->panel_info.pdest == DISPLAY_1) {
#if defined(CONFIG_FB_MSM_OVERLAY) && defined(CONFIG_FB_MSM_MDDI)
			mfd->dma_fnc = mdp4_mddi_overlay;
			mfd->cursor_update = mdp4_mddi_overlay_cursor;
#else
			mfd->dma_fnc = mdp_dma2_update;
#endif
			mfd->dma = &dma2_data;
			mfd->lut_update = mdp_lut_update_nonlcdc;
			mfd->do_histogram = mdp_do_histogram;
			mfd->start_histogram = mdp_histogram_start;
			mfd->stop_histogram = mdp_histogram_stop;
		} else {
			mfd->dma_fnc = mdp_dma_s_update;
			mfd->dma = &dma_s_data;
		}
#endif
		if (mdp_pdata)
			mfd->vsync_gpio = mdp_pdata->gpio;
		else
			mfd->vsync_gpio = -1;

#ifdef CONFIG_FB_MSM_MDP40
		mdp_pipe_ctrl(MDP_CMD_BLOCK, MDP_BLOCK_POWER_ON, FALSE);
		spin_lock_irqsave(&mdp_spin_lock, flag);
		mdp_intr_mask |= INTR_OVERLAY0_DONE;
		if (mdp_hw_revision < MDP4_REVISION_V2_1) {
			/* dmas dmap switch */
			mdp_intr_mask |= INTR_DMA_S_DONE;
		}
		outp32(MDP_INTR_ENABLE, mdp_intr_mask);
		spin_unlock_irqrestore(&mdp_spin_lock, flag);
		mdp_pipe_ctrl(MDP_CMD_BLOCK, MDP_BLOCK_POWER_OFF, FALSE);

		if (mfd->panel.type == EBI2_PANEL)
			intf = EBI2_INTF;
		else
			intf = MDDI_INTF;

		if (mfd->panel_info.pdest == DISPLAY_1)
			if_no = PRIMARY_INTF_SEL;
		else
			if_no = SECONDARY_INTF_SEL;

		mdp4_display_intf_sel(if_no, intf);
#endif
		mdp_config_vsync(mdp_init_pdev, mfd);
		break;

#ifdef CONFIG_FB_MSM_MIPI_DSI
	case MIPI_VIDEO_PANEL:
#ifndef CONFIG_FB_MSM_MDP303
		mipi = &mfd->panel_info.mipi;
		mfd->vsync_init = mdp4_dsi_vsync_init;
		mfd->vsync_show = mdp4_dsi_video_show_event;
		mfd->hw_refresh = TRUE;
		mfd->dma_fnc = mdp4_dsi_video_overlay;
		mfd->lut_update = mdp_lut_update_lcdc;
		mfd->do_histogram = mdp_do_histogram;
		mfd->start_histogram = mdp_histogram_start;
		mfd->stop_histogram = mdp_histogram_stop;
		if (mfd->panel_info.pdest == DISPLAY_1) {
			if_no = PRIMARY_INTF_SEL;
			mfd->dma = &dma2_data;
		} else {
			if_no = EXTERNAL_INTF_SEL;
			mfd->dma = &dma_e_data;
		}
		mdp4_display_intf_sel(if_no, DSI_VIDEO_INTF);
#else
		pdata->on = mdp_dsi_video_on;
		pdata->off = mdp_dsi_video_off;
		mfd->hw_refresh = TRUE;
		mfd->dma_fnc = mdp_dsi_video_update;
		mfd->do_histogram = mdp_do_histogram;
		mfd->start_histogram = mdp_histogram_start;
		mfd->stop_histogram = mdp_histogram_stop;
		mfd->vsync_ctrl = mdp_dma_video_vsync_ctrl;
		mfd->vsync_show = mdp_dma_video_show_event;
		if (mfd->panel_info.pdest == DISPLAY_1)
			mfd->dma = &dma2_data;
		else {
			printk(KERN_ERR "Invalid Selection of destination panel\n");
			rc = -ENODEV;
			mdp_clk_ctrl(0);
			goto mdp_probe_err;
		}

#endif
		if (mdp_rev >= MDP_REV_40)
			mfd->cursor_update = mdp_hw_cursor_sync_update;
		else
			mfd->cursor_update = mdp_hw_cursor_update;
		break;

	case MIPI_CMD_PANEL:
#ifndef CONFIG_FB_MSM_MDP303
		mfd->dma_fnc = mdp4_dsi_cmd_overlay;
		mipi = &mfd->panel_info.mipi;
		mfd->vsync_init = mdp4_dsi_rdptr_init;
		mfd->vsync_show = mdp4_dsi_cmd_show_event;
		if (mfd->panel_info.pdest == DISPLAY_1) {
			if_no = PRIMARY_INTF_SEL;
			mfd->dma = &dma2_data;
		} else {
			if_no = SECONDARY_INTF_SEL;
			mfd->dma = &dma_s_data;
		}
		mfd->lut_update = mdp_lut_update_nonlcdc;
		mfd->do_histogram = mdp_do_histogram;
		mfd->start_histogram = mdp_histogram_start;
		mfd->stop_histogram = mdp_histogram_stop;
		mdp4_display_intf_sel(if_no, DSI_CMD_INTF);
#else
		mfd->dma_fnc = mdp_dma2_update;
		mfd->do_histogram = mdp_do_histogram;
		mfd->start_histogram = mdp_histogram_start;
		mfd->stop_histogram = mdp_histogram_stop;
		mfd->vsync_ctrl = mdp_dma_vsync_ctrl;
		mfd->vsync_show = mdp_dma_show_event;
		if (mfd->panel_info.pdest == DISPLAY_1)
			mfd->dma = &dma2_data;
		else {
			printk(KERN_ERR "Invalid Selection of destination panel\n");
			rc = -ENODEV;
			mdp_clk_ctrl(0);
			goto mdp_probe_err;
		}
		INIT_WORK(&mfd->dma_update_worker,
			mdp_lcd_update_workqueue_handler);
#endif
		mdp_config_vsync(mdp_init_pdev, mfd);
		break;
#endif

#ifdef CONFIG_FB_MSM_DTV
	case DTV_PANEL:
		mfd->vsync_init = mdp4_dtv_vsync_init;
		mfd->vsync_show = mdp4_dtv_show_event;
		pdata->on = mdp4_dtv_on;
		pdata->off = mdp4_dtv_off;
		mfd->hw_refresh = TRUE;
		mfd->cursor_update = mdp_hw_cursor_update;
		mfd->dma_fnc = mdp4_dtv_overlay;
		mfd->dma = &dma_e_data;
		mfd->do_histogram = mdp_do_histogram;
		mfd->start_histogram = mdp_histogram_start;
		mfd->stop_histogram = mdp_histogram_stop;
		mdp4_display_intf_sel(EXTERNAL_INTF_SEL, DTV_INTF);
		break;
#endif
	case HDMI_PANEL:
	case LCDC_PANEL:
	case LVDS_PANEL:
#ifdef CONFIG_FB_MSM_MDP303
		pdata->on = mdp_lcdc_on;
		pdata->off = mdp_lcdc_off;
#endif
		mfd->hw_refresh = TRUE;
#if	defined(CONFIG_FB_MSM_OVERLAY) && defined(CONFIG_FB_MSM_MDP40)
		mfd->cursor_update = mdp_hw_cursor_sync_update;
#else
		mfd->cursor_update = mdp_hw_cursor_update;
#endif
#ifndef CONFIG_FB_MSM_MDP22
		mfd->lut_update = mdp_lut_update_lcdc;
		mfd->do_histogram = mdp_do_histogram;
		mfd->start_histogram = mdp_histogram_start;
		mfd->stop_histogram = mdp_histogram_stop;
#endif
#ifdef CONFIG_FB_MSM_OVERLAY
		mfd->dma_fnc = mdp4_lcdc_overlay;
#else
		mfd->dma_fnc = mdp_lcdc_update;
#endif

#ifdef CONFIG_FB_MSM_MDP40
		mfd->vsync_init = mdp4_lcdc_vsync_init;
		mfd->vsync_show = mdp4_lcdc_show_event;
		if (mfd->panel.type == HDMI_PANEL) {
			mfd->dma = &dma_e_data;
			mdp4_display_intf_sel(EXTERNAL_INTF_SEL, LCDC_RGB_INTF);
		} else {
			mfd->dma = &dma2_data;
			mdp4_display_intf_sel(PRIMARY_INTF_SEL, LCDC_RGB_INTF);
		}
#else
		mfd->dma = &dma2_data;
		mfd->vsync_ctrl = mdp_dma_lcdc_vsync_ctrl;
		mfd->vsync_show = mdp_dma_lcdc_show_event;
		spin_lock_irqsave(&mdp_spin_lock, flag);
		mdp_intr_mask &= ~MDP_DMA_P_DONE;
		outp32(MDP_INTR_ENABLE, mdp_intr_mask);
		spin_unlock_irqrestore(&mdp_spin_lock, flag);
#endif
		break;

	case TV_PANEL:
#if defined(CONFIG_FB_MSM_OVERLAY) && defined(CONFIG_FB_MSM_TVOUT)
		pdata->on = mdp4_atv_on;
		pdata->off = mdp4_atv_off;
		mfd->dma_fnc = mdp4_atv_overlay;
		mfd->dma = &dma_e_data;
		mdp4_display_intf_sel(EXTERNAL_INTF_SEL, TV_INTF);
#else
		pdata->on = mdp_dma3_on;
		pdata->off = mdp_dma3_off;
		mfd->hw_refresh = TRUE;
		mfd->dma_fnc = mdp_dma3_update;
		mfd->dma = &dma3_data;
#endif
		break;

#ifdef CONFIG_FB_MSM_WRITEBACK_MSM_PANEL
	case WRITEBACK_PANEL:
		{
			unsigned int mdp_version;
			mdp_pipe_ctrl(MDP_CMD_BLOCK, MDP_BLOCK_POWER_ON,
						 FALSE);
			mdp_version = inpdw(MDP_BASE + 0x0);
			mdp_pipe_ctrl(MDP_CMD_BLOCK, MDP_BLOCK_POWER_OFF,
						FALSE);
			if (mdp_version < 0x04030303) {
				pr_err("%s: writeback panel not supprted\n",
					 __func__);
				platform_device_put(msm_fb_dev);
				mdp_clk_ctrl(0);
				return -ENODEV;
			}
			mdp4_wfd_init(0);
			pdata->on = mdp4_overlay_writeback_on;
			pdata->off = mdp4_overlay_writeback_off;
			mfd->dma_fnc = mdp4_writeback_overlay;
			mfd->dma = &dma_wb_data;
			mutex_init(&mfd->writeback_mutex);
			mutex_init(&mfd->unregister_mutex);
			mdp4_display_intf_sel(EXTERNAL_INTF_SEL, DTV_INTF);
		}
		break;
#endif
	default:
		printk(KERN_ERR "mdp_probe: unknown device type!\n");
		rc = -ENODEV;
		mdp_clk_ctrl(0);
		goto mdp_probe_err;
	}
