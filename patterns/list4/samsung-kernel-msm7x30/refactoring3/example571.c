switch (mfd->panel.type) {
	case MIPI_CMD_PANEL:
		mdp4_dsi_cmd_pipe_commit(0, 1);
		break;
	case MIPI_VIDEO_PANEL:
		mdp4_dsi_video_pipe_commit(0, 1);
		break;
	case LVDS_PANEL:
	case LCDC_PANEL:
		mdp4_lcdc_pipe_commit(0, 1);
		break;
#ifdef CONFIG_FB_MSM_DTV
	case DTV_PANEL:
		mdp4_dtv_pipe_commit(0, 1);
		break;
#endif
#ifdef CONFIG_FB_MSM_WRITEBACK_MSM_PANEL
	case WRITEBACK_PANEL:
		mdp4_wfd_pipe_commit(mfd, 0, 1);
		break;
#endif
	default:
		pr_err("Panel Not Supported for Commit");
		ret = -EINVAL;
		break;
	}
