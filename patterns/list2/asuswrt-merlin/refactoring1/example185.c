if (pmhctl->link_state == MDDI_LINK_HIBERNATING) {
			mddi_host_disable_io_clock();
			mddi_host_disable_hclk();
		}
#ifdef FEATURE_MDDI_HOST_ENABLE_EARLY_HIBERNATION
		else if ((pmhctl->link_state == MDDI_LINK_ACTIVE) &&
			 (!pmhctl->disable_hibernation)) {
			mddi_host_reg_out(CMD, MDDI_CMD_POWERDOWN);
		}
#endif
