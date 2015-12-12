#ifdef SUPPORT_TX_MCAST2UNI
if (priv->pshare->rf_ft_var.mc2u_disable ||
							((((OPMODE & (WIFI_STATION_STATE|WIFI_ASOC_STATE))
							== (WIFI_STATION_STATE|WIFI_ASOC_STATE)) &&
							!checkIPMcAndReplace(priv, skb, &iph->daddr)) ||
							(OPMODE & WIFI_ADHOC_STATE)))
#endif
					{
						__nat25_generate_ipv4_network_addr(networkAddr, &iph->daddr);

						if (!__nat25_db_network_lookup_and_replace(priv, skb, networkAddr)) {
							if (*((unsigned char *)&iph->daddr + 3) == 0xff) {
								// L2 is unicast but L3 is broadcast, make L2 bacome broadcast
								DBG_871X("NAT25: Set DA as boardcast\n");
								memset(skb->data, 0xff, ETH_ALEN);
							}
							else {
								// forward unknow IP packet to upper TCP/IP
								DBG_871X("NAT25: Replace DA with BR's MAC\n");
								if ( (*(u32 *)priv->br_mac) == 0 && (*(u16 *)(priv->br_mac+4)) == 0 ) {
									void netdev_br_init(struct net_device *netdev);
									printk("Re-init netdev_br_init() due to br_mac==0!\n");
									netdev_br_init(priv->pnetdev);
								}
								memcpy(skb->data, priv->br_mac, ETH_ALEN);
							}
						}
					}
