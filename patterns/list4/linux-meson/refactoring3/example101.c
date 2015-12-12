switch (wValue) {
		case UHF_PORT_ENABLE:
			DWC_DEBUGPL(DBG_ANY, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_ENABLE\n");
			hprt0.d32 = dwc_otg_read_hprt0(core_if);
			hprt0.b.prtena = 1;
			DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			break;
		case UHF_PORT_SUSPEND:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_SUSPEND\n");

			if (core_if->power_down == 2) {
				dwc_otg_host_hibernation_restore(core_if, 0, 0);
			} else {
				DWC_WRITE_REG32(core_if->pcgcctl, 0);
				dwc_mdelay(5);

				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				hprt0.b.prtres = 1;
				DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
				hprt0.b.prtsusp = 0;
				/* Clear Resume bit */
				dwc_mdelay(100);
				hprt0.b.prtres = 0;
				DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			}
			break;
#ifdef CONFIG_USB_DWC_OTG_LPM
		case UHF_PORT_L1:
			{
				pcgcctl_data_t pcgcctl = {.d32 = 0 };
				glpmcfg_data_t lpmcfg = {.d32 = 0 };

				lpmcfg.d32 =
				    DWC_READ_REG32(&core_if->
						   core_global_regs->glpmcfg);
				lpmcfg.b.en_utmi_sleep = 0;
				lpmcfg.b.hird_thres &= (~(1 << 4));
				lpmcfg.b.prt_sleep_sts = 1;
				DWC_WRITE_REG32(&core_if->
						core_global_regs->glpmcfg,
						lpmcfg.d32);

				/* Clear Enbl_L1Gating bit. */
				pcgcctl.b.enbl_sleep_gating = 1;
				DWC_MODIFY_REG32(core_if->pcgcctl, pcgcctl.d32,
						 0);

				dwc_mdelay(5);

				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				hprt0.b.prtres = 1;
				DWC_WRITE_REG32(core_if->host_if->hprt0,
						hprt0.d32);
				/* This bit will be cleared in wakeup interrupt handle */
				break;
			}
#endif
		case UHF_PORT_POWER:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_POWER\n");
			hprt0.d32 = dwc_otg_read_hprt0(core_if);
			hprt0.b.prtpwr = 0;
			DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			break;
		case UHF_PORT_INDICATOR:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_INDICATOR\n");
			/* Port inidicator not supported */
			break;
		case UHF_C_PORT_CONNECTION:
			/* Clears drivers internal connect status change
			 * flag */
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_CONNECTION\n");
			dwc_otg_hcd->flags.b.port_connect_status_change = 0;
			break;
		case UHF_C_PORT_RESET:
			/* Clears the driver's internal Port Reset Change
			 * flag */
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_RESET\n");
			dwc_otg_hcd->flags.b.port_reset_change = 0;
			break;
		case UHF_C_PORT_ENABLE:
			/* Clears the driver's internal Port
			 * Enable/Disable Change flag */
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_ENABLE\n");
			dwc_otg_hcd->flags.b.port_enable_change = 0;
			break;
		case UHF_C_PORT_SUSPEND:
			/* Clears the driver's internal Port Suspend
			 * Change flag, which is set when resume signaling on
			 * the host port is complete */
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_SUSPEND\n");
			dwc_otg_hcd->flags.b.port_suspend_change = 0;
			break;
#ifdef CONFIG_USB_DWC_OTG_LPM
		case UHF_C_PORT_L1:
			dwc_otg_hcd->flags.b.port_l1_change = 0;
			break;
#endif
		case UHF_C_PORT_OVER_CURRENT:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_OVER_CURRENT\n");
			dwc_otg_hcd->flags.b.port_over_current_change = 0;
			break;
		default:
			retval = -DWC_E_INVALID;
			DWC_ERROR("DWC OTG HCD - "
				  "ClearPortFeature request %xh "
				  "unknown or unsupported\n", wValue);
		}
