#ifdef NICE_SUPPORT
if( pUmDevice->nice_rx ) {
			vlan_tag_t *vlan_tag;

			vlan_tag = (vlan_tag_t *) &skb->cb[0];
			if (pPacket->Flags & RCV_BD_FLAG_VLAN_TAG) {
				vlan_tag->signature = 0x7777;
				vlan_tag->tag = pPacket->VlanTag;
				/* Override vlan priority with dscp priority */
				if (dscp_prio)
					UPD_VLANTAG_PRIO(vlan_tag->tag,  dscp_prio);
			} else {
				vlan_tag->signature = 0;
			}
			pUmDevice->nice_rx(skb, pUmDevice->nice_ctx);
		} else
#endif
		{
#ifdef BCM_VLAN
			if (pUmDevice->vlgrp &&
				(pPacket->Flags & RCV_BD_FLAG_VLAN_TAG)) {
				/* Override vlan priority with dscp priority */
				if (dscp_prio)
					UPD_VLANTAG_PRIO(pPacket->VlanTag, dscp_prio);
#ifdef BCM_NAPI_RXPOLL
				vlan_hwaccel_receive_skb(skb, pUmDevice->vlgrp,
					pPacket->VlanTag);
#else
				vlan_hwaccel_rx(skb, pUmDevice->vlgrp,
					pPacket->VlanTag);
#endif
			} else
#endif
			{
#ifdef BCM_WL_EMULATOR
				if(pDevice->wl_emulate_rx) {
					/* bcmstats("emu recv %d %d"); */
					wlcemu_receive_skb(pDevice->wlc, skb);
					/* bcmstats("emu recv end %d %d"); */
				}
				else 
#endif /* BCM_WL_EMULATOR  */
				{
#ifdef BCM_NAPI_RXPOLL
				netif_receive_skb(skb);
#else
				netif_rx(skb);
#endif
				}
			}
		}
