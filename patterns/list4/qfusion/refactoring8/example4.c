static cmd_function_t cmdlist[] =
{
	{ "connect", TV_Connect_f },
#if defined(TCP_ALLOW_TVCONNECT)
	{ "tcpconnect", TV_TCPConnect_f },
#endif
	{ "disconnect", TV_Disconnect_f },

	{ "demo", TV_Demo_f },
	{ "record", TV_Record_f },
	{ "stop", TV_Stop_f },

	{ "status", TV_Status_f },
	{ "cmd", TV_Cmd_f },

	{ "rename", TV_Rename_f },

	{ "heartbeat", TV_Heartbeat_f },

	{ "music", TV_Music_f },

	{ NULL, NULL }
};
