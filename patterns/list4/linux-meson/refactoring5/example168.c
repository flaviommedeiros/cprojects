#ifdef CONFIG_INTEL_WIDI
if( widi_version == 35 )
	{
		RTW_PUT_LE16(p2pie + p2pielen, 21 + 8 + pwdinfo->device_name_len);
	}
	else if( widi_version == 40 )
	{
		RTW_PUT_LE16(p2pie + p2pielen, 21 + 8 * pmlmepriv->num_p2p_sdt + pwdinfo->device_name_len);
	}
	else
#endif //CONFIG_INTEL_WIDI
	RTW_PUT_LE16(p2pie + p2pielen, 21 + pwdinfo->device_name_len);
