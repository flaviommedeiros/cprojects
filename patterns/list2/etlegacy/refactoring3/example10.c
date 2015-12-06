switch (a.type)
	{
	case NA_LOOPBACK:
		return qtrue;
	case NA_IP:
	{
		addra = (byte *) &a.ip;
		addrb = (byte *) &b.ip;

		if (netmask < 0 || netmask > 32)
		{
			netmask = 32;
		}
	}
	break;
#ifdef FEATURE_IPV6
	case NA_IP6:
	{
		addra = (byte *) &a.ip6;
		addrb = (byte *) &b.ip6;

		if (netmask < 0 || netmask > 128)
		{
			netmask = 128;
		}
	}
	break;
#endif
	default:
		Com_Printf("NET_CompareBaseAdrMask: bad address type a: %i (b: %i, netmask: %i)\n", a.type, b.type, netmask);
		return qfalse;
	}
