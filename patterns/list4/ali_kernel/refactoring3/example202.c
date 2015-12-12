switch (musb->xceiv->state) {
		case OTG_STATE_A_HOST:
			musb->xceiv->state = OTG_STATE_A_SUSPEND;
			musb->is_active = is_otg_enabled(musb)
					&& musb->xceiv->host->b_hnp_enable;
			if (musb->is_active)
				mod_timer(&musb->otg_timer, jiffies
					+ msecs_to_jiffies(
						OTG_TIME_A_AIDL_BDIS));
			musb_platform_try_idle(musb, 0);
			break;
#ifdef	CONFIG_USB_MUSB_OTG
		case OTG_STATE_B_HOST:
			musb->xceiv->state = OTG_STATE_B_WAIT_ACON;
			musb->is_active = is_otg_enabled(musb)
					&& musb->xceiv->host->b_hnp_enable;
			musb_platform_try_idle(musb, 0);
			break;
#endif
		default:
			DBG(1, "bogus rh suspend? %s\n",
				otg_state_string(musb));
		}
