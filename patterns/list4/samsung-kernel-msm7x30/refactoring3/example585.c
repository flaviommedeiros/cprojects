switch (dssdev->type) {
#ifdef CONFIG_OMAP2_DSS_DPI
	case OMAP_DISPLAY_TYPE_DPI:
		r = dpi_init_display(dssdev);
		break;
#endif
#ifdef CONFIG_OMAP2_DSS_RFBI
	case OMAP_DISPLAY_TYPE_DBI:
		r = rfbi_init_display(dssdev);
		break;
#endif
#ifdef CONFIG_OMAP2_DSS_VENC
	case OMAP_DISPLAY_TYPE_VENC:
		r = venc_init_display(dssdev);
		break;
#endif
#ifdef CONFIG_OMAP2_DSS_SDI
	case OMAP_DISPLAY_TYPE_SDI:
		r = sdi_init_display(dssdev);
		break;
#endif
#ifdef CONFIG_OMAP2_DSS_DSI
	case OMAP_DISPLAY_TYPE_DSI:
		r = dsi_init_display(dssdev);
		break;
#endif
	case OMAP_DISPLAY_TYPE_HDMI:
		r = hdmi_init_display(dssdev);
		break;
	default:
		DSSERR("Support for display '%s' not compiled in.\n",
				dssdev->name);
		return;
	}
