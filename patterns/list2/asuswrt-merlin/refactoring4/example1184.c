#ifdef RTCONFIG_QTN
if (!Get_ChannelList_5G_qtn())
#else
		if (!Get_ChannelList_5G())
#endif
			puts("ATE_ERROR");
