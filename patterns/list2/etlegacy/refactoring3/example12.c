switch (a.type)
	{
	case NA_LOOPBACK:
		Com_sprintf(s, sizeof(s), "loopback");
		break;
	case NA_BOT:
		Com_sprintf(s, sizeof(s), "bot");
		break;
	case NA_IP:
		Com_sprintf(s, sizeof(s), "%s:%hu", NET_AdrToString(a), ntohs(a.port));
		break;
#ifdef FEATURE_IPV6
	case NA_IP6:
		Com_sprintf(s, sizeof(s), "[%s]:%hu", NET_AdrToString(a), ntohs(a.port));
		break;
#endif
	default:
		Com_Printf("NET_AdrToStringwPort: Unknown address type: %i\n", a.type);
		break;
	}
