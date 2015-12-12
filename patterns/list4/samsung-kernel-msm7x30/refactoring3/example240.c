switch (ctl.wValue) {
			case USB_DEVICE_TEST_MODE:
				switch (ctl.wIndex) {
				case J_TEST:
				case K_TEST:
				case SE0_NAK_TEST:
				case TST_PKT_TEST:
					atomic_set(&ui->test_mode, ctl.wIndex);
					goto ack;
				}
				goto stall;
			case USB_DEVICE_REMOTE_WAKEUP:
				atomic_set(&ui->remote_wakeup, 1);
				goto ack;
#ifdef CONFIG_USB_OTG
			case USB_DEVICE_B_HNP_ENABLE:
				ui->gadget.b_hnp_enable = 1;
				goto ack;
			case USB_DEVICE_A_HNP_SUPPORT:
			case USB_DEVICE_A_ALT_HNP_SUPPORT:
				/* B-devices compliant to OTG spec
				 * Rev 2.0 are not required to
				 * suppport these features.
				 */
				goto stall;
#endif
			}
