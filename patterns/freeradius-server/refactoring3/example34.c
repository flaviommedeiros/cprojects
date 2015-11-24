switch (listener->type) {
#ifdef WITH_PROXY
	case RAD_LISTEN_PROXY:
		limit = &sock->home->limit;
		break;
#endif

	case RAD_LISTEN_AUTH:
#ifdef WITH_ACCOUNTING
	case RAD_LISTEN_ACCT:
#endif
		limit = &sock->limit;
		break;

	default:
		return;
	}
