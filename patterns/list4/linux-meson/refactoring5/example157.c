#ifdef DBG_FIXED_CHAN
if(pmlmeext->fixed_chan !=0xff)
				set_channel_bwmode(padapter, pmlmeext->fixed_chan, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
			else	
#endif
				set_channel_bwmode(padapter, survey_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
