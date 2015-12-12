#ifdef  CONFIG_FB_OSD_SUPPORT_SYNC_FENCE
if (register_fiq_bridge_handle(&osd_hw.fiq_handle_item))
#else
	if (request_irq(INT_VIU_VSYNC, &vsync_isr,
			IRQF_SHARED , "am_osd_vsync", osd_setup))
#endif
	{
		amlog_level(LOG_LEVEL_HIGH, "can't request irq for vsync\n");
	}
