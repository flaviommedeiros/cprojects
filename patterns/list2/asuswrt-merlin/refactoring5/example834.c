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
