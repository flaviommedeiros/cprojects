#ifdef CONFIG_FILE_FWIMG
if (rtw_is_file_readable(rtw_fw_mp_bt_file_path) == _TRUE)
	{
		DBG_8192C("%s: accquire MP BT FW from file:%s\n", __FUNCTION__, rtw_fw_mp_bt_file_path);

		rtStatus = rtw_retrive_from_file(rtw_fw_mp_bt_file_path, FwBuffer, FW_8723B_SIZE);
		BTFirmwareLen = rtStatus>=0?rtStatus:0;
		pBTFirmwareBuf = FwBuffer;
	}
	else
#endif // CONFIG_FILE_FWIMG
	{
#ifdef CONFIG_EMBEDDED_FWIMG
		DBG_8192C("%s: Download MP BT FW from header\n", __FUNCTION__);

		pBTFirmwareBuf = (u8*)Rtl8723BFwBTImgArray;
		BTFirmwareLen = Rtl8723BFwBTImgArrayLength;
		pFirmware->szFwBuffer = pBTFirmwareBuf;
		pFirmware->ulFwLength = BTFirmwareLen;
#endif // CONFIG_EMBEDDED_FWIMG
	}
