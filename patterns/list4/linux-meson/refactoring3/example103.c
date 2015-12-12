switch (wValue) {
		case UHF_PORT_SUSPEND:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "SetPortFeature - USB_PORT_FEAT_SUSPEND\n");
			if (dwc_otg_hcd_otg_port(dwc_otg_hcd) != wIndex) {
				goto error;
			}
			if (core_if->power_down == 2) {
				int timeout = 300;
				dwc_irqflags_t flags;
				pcgcctl_data_t pcgcctl = {.d32 = 0 };
				gpwrdn_data_t gpwrdn = {.d32 = 0 };
				gusbcfg_data_t gusbcfg = {.d32 = 0 };
#ifdef DWC_DEV_SRPCAP
				int32_t otg_cap_param = core_if->core_params->otg_cap;
#endif
				DWC_PRINTF("Preparing for complete power-off\n");

				/* Save registers before hibernation */
				dwc_otg_save_global_regs(core_if);
				dwc_otg_save_host_regs(core_if);

				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				hprt0.b.prtsusp = 1;
				hprt0.b.prtena = 0;
				DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
				/* Spin hprt0.b.prtsusp to became 1 */
				do {
					hprt0.d32 = dwc_otg_read_hprt0(core_if);
					if (hprt0.b.prtsusp) {
						break;
					}
					dwc_mdelay(1);
				} while (--timeout);
				if (!timeout) {
					DWC_WARN("Suspend wasn't genereted\n");
				}
				dwc_udelay(10);

				/*
				 * We need to disable interrupts to prevent servicing of any IRQ
				 * during going to hibernation
				 */
				DWC_SPINLOCK_IRQSAVE(dwc_otg_hcd->lock, &flags);
				core_if->lx_state = DWC_OTG_L2;
#ifdef DWC_DEV_SRPCAP
				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				hprt0.b.prtpwr = 0;
				hprt0.b.prtena = 0;
				DWC_WRITE_REG32(core_if->host_if->hprt0,
						hprt0.d32);
#endif
				gusbcfg.d32 =
				    DWC_READ_REG32(&core_if->core_global_regs->
						   gusbcfg);
				if (gusbcfg.b.ulpi_utmi_sel == 1) {
					/* ULPI interface */
					/* Suspend the Phy Clock */
					pcgcctl.d32 = 0;
					pcgcctl.b.stoppclk = 1;
					DWC_MODIFY_REG32(core_if->pcgcctl, 0,
							 pcgcctl.d32);
					dwc_udelay(10);
					gpwrdn.b.pmuactv = 1;
					DWC_MODIFY_REG32(&core_if->
							 core_global_regs->
							 gpwrdn, 0, gpwrdn.d32);
				} else {
					/* UTMI+ Interface */
					gpwrdn.b.pmuactv = 1;
					DWC_MODIFY_REG32(&core_if->
							 core_global_regs->
							 gpwrdn, 0, gpwrdn.d32);
					dwc_udelay(10);
					pcgcctl.b.stoppclk = 1;
					DWC_MODIFY_REG32(core_if->pcgcctl, 0, pcgcctl.d32);
					dwc_udelay(10);
				}
#ifdef DWC_DEV_SRPCAP
				gpwrdn.d32 = 0;
				gpwrdn.b.dis_vbus = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
#endif
				gpwrdn.d32 = 0;
				gpwrdn.b.pmuintsel = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
				dwc_udelay(10);

				gpwrdn.d32 = 0;
#ifdef DWC_DEV_SRPCAP
				gpwrdn.b.srp_det_msk = 1;
#endif
				gpwrdn.b.disconn_det_msk = 1;
				gpwrdn.b.lnstchng_msk = 1;
				gpwrdn.b.sts_chngint_msk = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
				dwc_udelay(10);

				/* Enable Power Down Clamp and all interrupts in GPWRDN */
				gpwrdn.d32 = 0;
				gpwrdn.b.pwrdnclmp = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
				dwc_udelay(10);

				/* Switch off VDD */
				gpwrdn.d32 = 0;
				gpwrdn.b.pwrdnswtch = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);

#ifdef DWC_DEV_SRPCAP
				if (otg_cap_param == DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE)
				{
					core_if->pwron_timer_started = 1;
					DWC_TIMER_SCHEDULE(core_if->pwron_timer, 6000 /* 6 secs */ );
				}
#endif
				/* Save gpwrdn register for further usage if stschng interrupt */
				core_if->gr_backup->gpwrdn_local =
						DWC_READ_REG32(&core_if->core_global_regs->gpwrdn);

				/* Set flag to indicate that we are in hibernation */
				core_if->hibernation_suspend = 1;
				DWC_SPINUNLOCK_IRQRESTORE(dwc_otg_hcd->lock,flags);

				DWC_PRINTF("Host hibernation completed\n");
				// Exit from case statement
				break;

			}
			if (dwc_otg_hcd_otg_port(dwc_otg_hcd) == wIndex &&
			    dwc_otg_hcd->fops->get_b_hnp_enable(dwc_otg_hcd)) {
				gotgctl_data_t gotgctl = {.d32 = 0 };
				gotgctl.b.hstsethnpen = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gotgctl, 0, gotgctl.d32);
				core_if->op_state = A_SUSPEND;
			}
			hprt0.d32 = dwc_otg_read_hprt0(core_if);
			hprt0.b.prtsusp = 1;
			DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			{
				dwc_irqflags_t flags;
				/* Update lx_state */
				DWC_SPINLOCK_IRQSAVE(dwc_otg_hcd->lock, &flags);
				core_if->lx_state = DWC_OTG_L2;
				DWC_SPINUNLOCK_IRQRESTORE(dwc_otg_hcd->lock, flags);
			}
			/* Suspend the Phy Clock */
			{
				pcgcctl_data_t pcgcctl = {.d32 = 0 };
				pcgcctl.b.stoppclk = 1;
				DWC_MODIFY_REG32(core_if->pcgcctl, 0,
						 pcgcctl.d32);
				dwc_udelay(10);
			}

			/* For HNP the bus must be suspended for at least 200ms. */
			if (dwc_otg_hcd->fops->get_b_hnp_enable(dwc_otg_hcd)) {
				pcgcctl_data_t pcgcctl = {.d32 = 0 };
				pcgcctl.b.stoppclk = 1;
                DWC_MODIFY_REG32(core_if->pcgcctl, pcgcctl.d32, 0);
				dwc_mdelay(200);
			}

			/** @todo - check how sw can wait for 1 sec to check asesvld??? */
#if 0 //vahrama !!!!!!!!!!!!!!!!!!
			if (core_if->adp_enable) {
				gotgctl_data_t gotgctl = {.d32 = 0 };
				gpwrdn_data_t gpwrdn;

				while (gotgctl.b.asesvld == 1) {
					gotgctl.d32 =
					    DWC_READ_REG32(&core_if->
							   core_global_regs->
							   gotgctl);
					dwc_mdelay(100);
				}

				/* Enable Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.pmuactv = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);

				/* Unmask SRP detected interrupt from Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.srp_det_msk = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);

				dwc_otg_adp_probe_start(core_if);
			}
#endif
			break;
		case UHF_PORT_POWER:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "SetPortFeature - USB_PORT_FEAT_POWER\n");
			hprt0.d32 = dwc_otg_read_hprt0(core_if);
			hprt0.b.prtpwr = 1;
			DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			break;
		case UHF_PORT_RESET:
			if ((core_if->power_down == 2)
			    && (core_if->hibernation_suspend == 1)) {
				/* If we are going to exit from Hibernated
				 * state via USB RESET.
				 */
				dwc_otg_host_hibernation_restore(core_if, 0, 1);
			} else {
				hprt0.d32 = dwc_otg_read_hprt0(core_if);

				DWC_DEBUGPL(DBG_HCD,
					    "DWC OTG HCD HUB CONTROL - "
					    "SetPortFeature - USB_PORT_FEAT_RESET\n");
				{
					pcgcctl_data_t pcgcctl = {.d32 = 0 };
					pcgcctl.b.enbl_sleep_gating = 1;
					pcgcctl.b.stoppclk = 1;
					DWC_MODIFY_REG32(core_if->pcgcctl, pcgcctl.d32, 0);
					DWC_WRITE_REG32(core_if->pcgcctl, 0);
				}
#ifdef CONFIG_USB_DWC_OTG_LPM
				{
					glpmcfg_data_t lpmcfg;
					lpmcfg.d32 =
						DWC_READ_REG32(&core_if->core_global_regs->glpmcfg);
					if (lpmcfg.b.prt_sleep_sts) {
						lpmcfg.b.en_utmi_sleep = 0;
						lpmcfg.b.hird_thres &= (~(1 << 4));
						DWC_WRITE_REG32
						    (&core_if->core_global_regs->glpmcfg,
						     lpmcfg.d32);
						dwc_mdelay(1);
					}
				}
#endif
				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				/* Clear suspend bit if resetting from suspended state. */
				hprt0.b.prtsusp = 0;
				/* When B-Host the Port reset bit is set in
				 * the Start HCD Callback function, so that
				 * the reset is started within 1ms of the HNP
				 * success interrupt. */
				if (!dwc_otg_hcd_is_b_host(dwc_otg_hcd)) {
					hprt0.b.prtpwr = 1;
					hprt0.b.prtrst = 1;
					DWC_PRINTF("Indeed it is in host mode hprt0 = %08x\n",hprt0.d32);
					DWC_WRITE_REG32(core_if->host_if->hprt0,
							hprt0.d32);
				}
				/* Clear reset bit in 10ms (FS/LS) or 50ms (HS) */
				dwc_mdelay(60);
				hprt0.b.prtrst = 0;
				DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
				core_if->lx_state = DWC_OTG_L0;	/* Now back to the on state */
			}
			break;
#ifdef DWC_HS_ELECT_TST
		case UHF_PORT_TEST:
			{
				uint32_t t;
				gintmsk_data_t gintmsk;

				t = (wIndex >> 8);	/* MSB wIndex USB */
				DWC_DEBUGPL(DBG_HCD,
					    "DWC OTG HCD HUB CONTROL - "
					    "SetPortFeature - USB_PORT_FEAT_TEST %d\n",
					    t);
				DWC_WARN("USB_PORT_FEAT_TEST %d\n", t);
				if (t < 6) {
					hprt0.d32 = dwc_otg_read_hprt0(core_if);
					hprt0.b.prttstctl = t;
					DWC_WRITE_REG32(core_if->host_if->hprt0,
							hprt0.d32);
				} else {
					/* Setup global vars with reg addresses (quick and
					 * dirty hack, should be cleaned up)
					 */
					global_regs = core_if->core_global_regs;
					hc_global_regs =
					    core_if->host_if->host_global_regs;
					hc_regs =
					    (dwc_otg_hc_regs_t *) ((char *)
								   global_regs +
								   0x500);
					data_fifo =
					    (uint32_t *) ((char *)global_regs +
							  0x1000);

					if (t == 6) {	/* HS_HOST_PORT_SUSPEND_RESUME */
						/* Save current interrupt mask */
						gintmsk.d32 =
						    DWC_READ_REG32
						    (&global_regs->gintmsk);

						/* Disable all interrupts while we muck with
						 * the hardware directly
						 */
						DWC_WRITE_REG32(&global_regs->gintmsk, 0);

						/* 15 second delay per the test spec */
						dwc_mdelay(15000);

						/* Drive suspend on the root port */
						hprt0.d32 =
						    dwc_otg_read_hprt0(core_if);
						hprt0.b.prtsusp = 1;
						hprt0.b.prtres = 0;
						DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);

						/* 15 second delay per the test spec */
						dwc_mdelay(15000);

						/* Drive resume on the root port */
						hprt0.d32 =
						    dwc_otg_read_hprt0(core_if);
						hprt0.b.prtsusp = 0;
						hprt0.b.prtres = 1;
						DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
						dwc_mdelay(100);

						/* Clear the resume bit */
						hprt0.b.prtres = 0;
						DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);

						/* Restore interrupts */
						DWC_WRITE_REG32(&global_regs->gintmsk, gintmsk.d32);
					} else if (t == 7) {	/* SINGLE_STEP_GET_DEVICE_DESCRIPTOR setup */
						/* Save current interrupt mask */
						gintmsk.d32 =
						    DWC_READ_REG32
						    (&global_regs->gintmsk);

						/* Disable all interrupts while we muck with
						 * the hardware directly
						 */
						DWC_WRITE_REG32(&global_regs->gintmsk, 0);

						/* 15 second delay per the test spec */
						dwc_mdelay(15000);

						/* Send the Setup packet */
						do_setup();

						/* 15 second delay so nothing else happens for awhile */
						dwc_mdelay(15000);

						/* Restore interrupts */
						DWC_WRITE_REG32(&global_regs->gintmsk, gintmsk.d32);
					} else if (t == 8) {	/* SINGLE_STEP_GET_DEVICE_DESCRIPTOR execute */
						/* Save current interrupt mask */
						gintmsk.d32 =
						    DWC_READ_REG32
						    (&global_regs->gintmsk);

						/* Disable all interrupts while we muck with
						 * the hardware directly
						 */
						DWC_WRITE_REG32(&global_regs->gintmsk, 0);

						/* Send the Setup packet */
						do_setup();

						/* 15 second delay so nothing else happens for awhile */
						dwc_mdelay(15000);

						/* Send the In and Ack packets */
						do_in_ack();

						/* 15 second delay so nothing else happens for awhile */
						dwc_mdelay(15000);

						/* Restore interrupts */
						DWC_WRITE_REG32(&global_regs->gintmsk, gintmsk.d32);
					}
				}
				break;
			}
#endif /* DWC_HS_ELECT_TST */

		case UHF_PORT_INDICATOR:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "SetPortFeature - USB_PORT_FEAT_INDICATOR\n");
			/* Not supported */
			break;
		default:
			retval = -DWC_E_INVALID;
			DWC_ERROR("DWC OTG HCD - "
				  "SetPortFeature request %xh "
				  "unknown or unsupported\n", wValue);
			break;
		}
