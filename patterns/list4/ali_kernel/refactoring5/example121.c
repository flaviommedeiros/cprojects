#ifdef DOT11_N_SUPPORT
if (ht_setting.field.MODE >= MODE_HTMIX)
    {
//	rate_index = 12 + ((UCHAR)ht_setting.field.BW *16) + ((UCHAR)ht_setting.field.ShortGI *32) + ((UCHAR)ht_setting.field.MCS);
	rate_index = 12 + ((UCHAR)ht_setting.field.BW *24) + ((UCHAR)ht_setting.field.ShortGI *48) + ((UCHAR)ht_setting.field.MCS);
    }
    else
#endif // DOT11_N_SUPPORT //
    if (ht_setting.field.MODE == MODE_OFDM)
	rate_index = (UCHAR)(ht_setting.field.MCS) + 4;
    else if (ht_setting.field.MODE == MODE_CCK)
	rate_index = (UCHAR)(ht_setting.field.MCS);
