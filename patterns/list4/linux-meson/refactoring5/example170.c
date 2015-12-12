#ifdef CONFIG_INTEL_WIDI
if( widi_version == 35 )
	{
		p2pie[ p2pielen++ ] = 0x01;
		
		RTW_PUT_BE16(p2pie + p2pielen, WPS_PDT_CID_DISPLAYS);
		p2pielen += 2;

		RTW_PUT_BE32(p2pie + p2pielen, INTEL_DEV_TYPE_OUI);
		p2pielen += 4;

		RTW_PUT_BE16(p2pie + p2pielen, P2P_SCID_WIDI_CONSUMER_SINK);
		p2pielen += 2;
	}
	else if( widi_version == 40 )
	{
		p2pie[ p2pielen++ ] = pmlmepriv->num_p2p_sdt;
		for( ; i < pmlmepriv->num_p2p_sdt; i++ )
		{
			RTW_PUT_BE16(p2pie + p2pielen, pmlmepriv->p2p_sdt_cid[i]);
			p2pielen += 2;

			RTW_PUT_BE32(p2pie + p2pielen, INTEL_DEV_TYPE_OUI);
			p2pielen += 4;

			RTW_PUT_BE16(p2pie + p2pielen, pmlmepriv->p2p_sdt_scid[i]);
			p2pielen += 2;
		}
	}
	else
#endif //CONFIG_INTEL_WIDI
	p2pie[ p2pielen++ ] = 0x00;
