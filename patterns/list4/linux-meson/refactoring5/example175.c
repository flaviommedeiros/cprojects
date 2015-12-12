#if 1
if(BT_INFO_LENGTH != btInfoLen)
	{
		status = HCI_STATUS_INVALID_HCI_CMD_PARA_VALUE;
		DBG_871X("Error BT Info Length: %d\n",btInfoLen);
		//return _FAIL;
	}
	else
#endif
	{
		if(0x1 == btInfoReason || 0x2 == btInfoReason)
		{
			_rtw_memcpy(btinfo, &pcmd[4], btInfoLen);
			btinfo[0] = btInfoReason;
			rtw_btcoex_btinfo_cmd(padapter,btinfo,btInfoLen);
		}
		else
		{
			DBG_871X("Other BT info reason\n");
		}
	}
