#ifdef PRINTER_SUPPORT
if (!CAN_PRINT(conn))
#endif
	{
		reply_nterror(req, NT_STATUS_ACCESS_DENIED);
		END_PROFILE(SMBsplretq);
		return;
	}
