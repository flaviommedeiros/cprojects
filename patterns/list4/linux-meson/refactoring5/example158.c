#ifdef DBG_FIXED_CHAN
if(pmlmeext->fixed_chan!=0xff)
				SelectChannel(padapter, pmlmeext->fixed_chan);
			else	
#endif
				SelectChannel(padapter, survey_channel);
