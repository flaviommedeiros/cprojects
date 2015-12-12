#ifdef	CONFIG_CONCURRENT_MODE
if(co_channel !=remain_ch)
#endif
				{
					//if (!padapter->mlmepriv.LinkDetectInfo.bBusyTraffic)
					set_channel_bwmode(padapter, remain_ch, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
				}
