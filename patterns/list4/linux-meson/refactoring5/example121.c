#ifdef CONFIG_80211AC_VHT
if(vht_cap == _TRUE) {
		max_rate = vht_data_rate;
	}
	else
#endif		
	if(ht_cap == _TRUE)
	{
		if(mcs_rate&0x8000)//MCS15
		{
			max_rate = (bw_40MHz) ? ((short_GI)?300:270):((short_GI)?144:130);
			
		}
		else if(mcs_rate&0x0080)//MCS7
		{
			max_rate = (bw_40MHz) ? ((short_GI)?150:135):((short_GI)?72:65);
		}
		else//default MCS7
		{
			//DBG_871X("wx_get_scan, mcs_rate_bitmap=0x%x\n", mcs_rate);
			max_rate = (bw_40MHz) ? ((short_GI)?150:135):((short_GI)?72:65);
		}

		max_rate = max_rate*2;//Mbps/2;		
	}
