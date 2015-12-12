#ifdef _WIN32
if (!j->adp)
#else
		if (!j->pcap)
#endif
		{
			result = ERROR_INVALID_PARAMETER;
			break;
		}
