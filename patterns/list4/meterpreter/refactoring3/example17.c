switch (u.sin.sin_family) {
	case AF_INET:
		inet_ntop(AF_INET, &u.sin.sin_addr, ret, sizeof ret);
		break;
#ifdef HAS_INET6_STRUCTS
	case AF_INET6:
		inet_ntop(AF_INET6, &u.sin6.sin6_addr, ret, sizeof ret);
		break;
#endif
	default:
		sprintf(ret, "[af%d]", u.sin.sin_family);
		break;
	}
