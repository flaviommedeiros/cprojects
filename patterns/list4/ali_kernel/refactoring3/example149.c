switch ( priv->timerType ) {
#ifdef MONITOR
		case TLAN_TIMER_LINK_BEAT:
			TLan_PhyMonitor( dev );
			break;
#endif
		case TLAN_TIMER_PHY_PDOWN:
			TLan_PhyPowerDown( dev );
			break;
		case TLAN_TIMER_PHY_PUP:
			TLan_PhyPowerUp( dev );
			break;
		case TLAN_TIMER_PHY_RESET:
			TLan_PhyReset( dev );
			break;
		case TLAN_TIMER_PHY_START_LINK:
			TLan_PhyStartLink( dev );
			break;
		case TLAN_TIMER_PHY_FINISH_AN:
			TLan_PhyFinishAutoNeg( dev );
			break;
		case TLAN_TIMER_FINISH_RESET:
			TLan_FinishReset( dev );
			break;
		case TLAN_TIMER_ACTIVITY:
			spin_lock_irqsave(&priv->lock, flags);
			if ( priv->timer.function == NULL ) {
				elapsed = jiffies - priv->timerSetAt;
				if ( elapsed >= TLAN_TIMER_ACT_DELAY ) {
					TLan_DioWrite8( dev->base_addr,
							TLAN_LED_REG, TLAN_LED_LINK );
				} else  {
					priv->timer.function = &TLan_Timer;
					priv->timer.expires = priv->timerSetAt
						+ TLAN_TIMER_ACT_DELAY;
					spin_unlock_irqrestore(&priv->lock, flags);
					add_timer( &priv->timer );
					break;
				}
			}
			spin_unlock_irqrestore(&priv->lock, flags);
			break;
		default:
			break;
	}
