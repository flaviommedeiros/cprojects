#if defined(CONFIG_STA_MODE_SCAN_UNDER_AP_MODE) || defined(CONFIG_ATMEL_RC_PATCH)
if (padapter->mlmeextpriv.mlmext_info.scan_cnt != RTW_SCAN_NUM_OF_CH
				|| padapter->mlmeextpriv.mlmext_info.backop_cnt == RTW_STAY_AP_CH_MILLISECOND)
#endif
				pmlmeext->sitesurvey_res.channel_idx++;
