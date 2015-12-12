#ifdef  WL_CFG80211
if (!(dhd->op_mode & DHD_FLAG_STA_MODE))
		return FALSE;
	else
#endif /* WL_CFG80211 */
		return TRUE;
