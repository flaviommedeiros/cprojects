#ifdef _WIN32
if (!j->adp || j->active == 1)
#else
		if (!j->pcap || j->active == 1)
#endif
		{
			result = ERROR_INVALID_PARAMETER;
			break;
		}
