#ifdef CONFIG_XMIT_ACK
if(psta->sta_stats.last_rx_data_pkts >= psta->sta_stats.rx_data_pkts)
#else
						if((psta->sta_stats.last_rx_data_pkts >= psta->sta_stats.rx_data_pkts) &&
							(!(psta->tdls_sta_state & TDLS_ALIVE_STATE)) )
#endif
						{
							if(psta->alive_count < ALIVE_MAX)
							{
								_rtw_memcpy(checkalive[num_checkalive].addr, psta->hwaddr, ETH_ALEN);
								checkalive[num_checkalive].psta = psta;
								num_checkalive++;
							}
							else
							{
								_rtw_memcpy(teardown[num_teardown].addr, psta->hwaddr, ETH_ALEN);
								teardown[num_teardown].psta = psta;
								num_teardown++;
							}
						}
						else
						{
							psta->tdls_sta_state &= (~TDLS_ALIVE_STATE);
							psta->alive_count = 0;
						}
