#ifdef CONFIG_INTEL_WIDI
if( widi_version == 40 )
	{
		//	Primary Device Type
		//	Category ID
		//*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( WPS_PDT_CID_MULIT_MEDIA );
		RTW_PUT_BE16(p2pie + p2pielen, pmlmepriv->p2p_pdt_cid );
		p2pielen += 2;

		//	OUI
		//*(u32*) ( p2pie + p2pielen ) = cpu_to_be32( WPSOUI );
		RTW_PUT_BE32(p2pie + p2pielen, WPSOUI);
		p2pielen += 4;

		//	Sub Category ID
		//*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( WPS_PDT_SCID_MEDIA_SERVER );
		RTW_PUT_BE16(p2pie + p2pielen, pmlmepriv->p2p_pdt_scid);
		p2pielen += 2;
	}
	else
#endif //CONFIG_INTEL_WIDI
	{
		//	Primary Device Type
		//	Category ID
		//*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( WPS_PDT_CID_MULIT_MEDIA );
		RTW_PUT_BE16(p2pie + p2pielen, WPS_PDT_CID_MULIT_MEDIA);
		p2pielen += 2;

		//	OUI
		//*(u32*) ( p2pie + p2pielen ) = cpu_to_be32( WPSOUI );
		RTW_PUT_BE32(p2pie + p2pielen, WPSOUI);
		p2pielen += 4;

		//	Sub Category ID
		//*(u16*) ( p2pie + p2pielen ) = cpu_to_be16( WPS_PDT_SCID_MEDIA_SERVER );
		RTW_PUT_BE16(p2pie + p2pielen, WPS_PDT_SCID_MEDIA_SERVER);
		p2pielen += 2;
	}
