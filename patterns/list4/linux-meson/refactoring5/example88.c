#ifdef CONFIG_FILE_FWIMG
if (rtw_is_file_readable(fwfilepath) == _TRUE)
	{
		DBG_8192C("%s accquire FW from file:%s\n", __FUNCTION__, fwfilepath);
		pFirmware->eFWSource = FW_SOURCE_IMG_FILE;
	}
	else
#endif // CONFIG_FILE_FWIMG
	{
#ifdef CONFIG_EMBEDDED_FWIMG
		pFirmware->eFWSource = FW_SOURCE_HEADER_FILE;
#else // !CONFIG_EMBEDDED_FWIMG
		pFirmware->eFWSource = FW_SOURCE_IMG_FILE; // We should decided by Reg.
#endif // !CONFIG_EMBEDDED_FWIMG
	}
