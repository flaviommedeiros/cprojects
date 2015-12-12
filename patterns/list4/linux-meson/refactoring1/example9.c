if((skb_queue_len(&priv->ieee80211->skb_waitQ[queue_index]) != 0)&&\
					(!(priv->ieee80211->queue_stop))) {
				if(NULL != (skb = skb_dequeue(&(priv->ieee80211->skb_waitQ[queue_index]))))
					priv->ieee80211->softmac_hard_start_xmit(skb, dev);

				return; //modified by david to avoid further processing AMSDU
			}
#ifdef USB_TX_DRIVER_AGGREGATION_ENABLE
			else if ((skb_queue_len(&priv->ieee80211->skb_drv_aggQ[queue_index])!= 0)&&\
				(!(priv->ieee80211->queue_stop))) {
				// Tx Driver Aggregation process
				/* The driver will aggregation the packets according to the following stats
				 * 1. check whether there's tx irq available, for it's a completion return
				 *    function, it should contain enough tx irq;
				 * 2. check packet type;
				 * 3. initialize sendlist, check whether the to-be send packet no greater than 1
				 * 4. aggregates the packets, and fill firmware info and tx desc into it, etc.
				 * 5. check whether the packet could be sent, otherwise just insert into wait head
				 * */
				skb = skb_dequeue(&priv->ieee80211->skb_drv_aggQ[queue_index]);
				if(!check_nic_enough_desc(dev, queue_index)) {
					skb_queue_head(&(priv->ieee80211->skb_drv_aggQ[queue_index]), skb);
					return;
				}

				{
					/*TODO*/
					/*
					u8* pHeader = skb->data;

					if(IsMgntQosData(pHeader) ||
					    IsMgntQData_Ack(pHeader) ||
					    IsMgntQData_Poll(pHeader) ||
					    IsMgntQData_Poll_Ack(pHeader)
					  )
					*/
					{
						struct ieee80211_drv_agg_txb SendList;

						memset(&SendList, 0, sizeof(struct ieee80211_drv_agg_txb));
						if(DrvAggr_GetAggregatibleList(dev, skb, &SendList) > 1) {
							skb = DrvAggr_Aggregation(dev, &SendList);

						}
					}
					priv->ieee80211->softmac_hard_start_xmit(skb, dev);
				}
			}
#endif
