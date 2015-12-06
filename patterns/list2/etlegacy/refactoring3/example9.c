switch (family)
	{
	case NA_IP:
		fam = AF_INET;
		break;
#ifdef FEATURE_IPV6
	case NA_IP6:
		fam = AF_INET6;
		break;
#endif
	default:
		fam = AF_UNSPEC;
		break;
	}
