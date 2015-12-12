switch (priv->timer_type) {
#ifdef MONITOR
	case TLAN_TIMER_LINK_BEAT:
		tlan_phy_monitor(dev);
		break;
#endif
	case TLAN_TIMER_PHY_PDOWN:
		tlan_phy_power_down(dev);
		break;
	case TLAN_TIMER_PHY_PUP:
		tlan_phy_power_up(dev);
		break;
	case TLAN_TIMER_PHY_RESET:
		tlan_phy_reset(dev);
		break;
	case TLAN_TIMER_PHY_START_LINK:
		tlan_phy_start_link(dev);
		break;
	case TLAN_TIMER_PHY_FINISH_AN:
		tlan_phy_finish_auto_neg(dev);
		break;
	case TLAN_TIMER_FINISH_RESET:
		tlan_finish_reset(dev);
		break;
	case TLAN_TIMER_ACTIVITY:
		spin_lock_irqsave(&priv->lock, flags);
		if (priv->timer.function == NULL) {
			elapsed = jiffies - priv->timer_set_at;
			if (elapsed >= TLAN_TIMER_ACT_DELAY) {
				tlan_dio_write8(dev->base_addr,
						TLAN_LED_REG, TLAN_LED_LINK);
			} else  {
				priv->timer.function = tlan_timer;
				priv->timer.expires = priv->timer_set_at
					+ TLAN_TIMER_ACT_DELAY;
				spin_unlock_irqrestore(&priv->lock, flags);
				add_timer(&priv->timer);
				break;
			}
		}
		spin_unlock_irqrestore(&priv->lock, flags);
		break;
	default:
		break;
	}
