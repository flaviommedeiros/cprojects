if (localIP[i].type == NA_IP)
		{
			Com_Printf("IP: %s\n", addrbuf);
		}
#ifdef FEATURE_IPV6
		else if (localIP[i].type == NA_IP6)
		{
			Com_Printf("IP6: %s\n", addrbuf);
		}
#endif
