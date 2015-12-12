#ifdef USB_TX_DRIVER_AGGREGATION_ENABLE
if((skb_queue_len(&priv->ieee80211->skb_waitQ[QueueID]) == 0) && (skb_queue_len(&priv->ieee80211->skb_aggQ[QueueID]) == 0) && (skb_queue_len(&priv->ieee80211->skb_drv_aggQ[QueueID]) == 0))
#else
			if((skb_queue_len(&priv->ieee80211->skb_waitQ[QueueID]) == 0)  && (skb_queue_len(&priv->ieee80211->skb_aggQ[QueueID]) == 0))
#endif
				continue;
