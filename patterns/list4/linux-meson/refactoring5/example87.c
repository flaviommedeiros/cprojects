#ifdef CONFIG_WOWLAN
if (bUsedWoWLANFw)
	{
		fwfilepath = rtw_fw_wow_file_path;
	}
	else
#endif // CONFIG_WOWLAN
	{
		fwfilepath = rtw_fw_file_path;
	}
