#ifdef CONFIG_INTEL_PROXIM
if((padapter->proximity.proxim_on==_TRUE)&&(pattrib->intel_proxim==_TRUE)){
			DBG_871X("\n %s pattrib->rate=%d\n",__FUNCTION__,pattrib->rate);
			SET_TX_DESC_TX_RATE_8723B(pbuf, pattrib->rate);
		}
		else
#endif
		{
			SET_TX_DESC_TX_RATE_8723B(pbuf, MRateToHwRate(pmlmeext->tx_rate));
		}
