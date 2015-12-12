switch (ctrlrequest->wValue) {
				case USB_DEVICE_REMOTE_WAKEUP:
					musb->may_wakeup = 1;
					break;
				case USB_DEVICE_TEST_MODE:
					if (musb->g.speed != USB_SPEED_HIGH)
						goto stall;
					if (ctrlrequest->wIndex & 0xff)
						goto stall;

					switch (ctrlrequest->wIndex >> 8) {
					case 1:
						pr_debug("TEST_J\n");
						/* TEST_J */
						musb->test_mode_nr =
							MUSB_TEST_J;
						break;
					case 2:
						/* TEST_K */
						pr_debug("TEST_K\n");
						musb->test_mode_nr =
							MUSB_TEST_K;
						break;
					case 3:
						/* TEST_SE0_NAK */
						pr_debug("TEST_SE0_NAK\n");
						musb->test_mode_nr =
							MUSB_TEST_SE0_NAK;
						break;
					case 4:
						/* TEST_PACKET */
						pr_debug("TEST_PACKET\n");
						musb->test_mode_nr =
							MUSB_TEST_PACKET;
						break;
					default:
						goto stall;
					}

					/* enter test mode after irq */
					if (handled > 0)
						musb->test_mode = true;
					break;
#ifdef CONFIG_USB_MUSB_OTG
				case USB_DEVICE_B_HNP_ENABLE:
					if (!musb->g.is_otg)
						goto stall;
					musb->g.b_hnp_enable = 1;
					musb_try_b_hnp_enable(musb);
					break;
				case USB_DEVICE_A_HNP_SUPPORT:
					if (!musb->g.is_otg)
						goto stall;
					musb->g.a_hnp_support = 1;
					break;
				case USB_DEVICE_A_ALT_HNP_SUPPORT:
					if (!musb->g.is_otg)
						goto stall;
					musb->g.a_alt_hnp_support = 1;
					break;
#endif
stall:
				default:
					handled = -EINVAL;
					break;
				}
