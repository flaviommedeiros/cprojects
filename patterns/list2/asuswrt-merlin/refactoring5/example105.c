#ifdef RTCONFIG_BCMWL6
if (info->vht_cap)
								NetWorkType = Ndis802_11OFDM5_VHT;
							else
#endif
								NetWorkType = Ndis802_11OFDM5_N;
