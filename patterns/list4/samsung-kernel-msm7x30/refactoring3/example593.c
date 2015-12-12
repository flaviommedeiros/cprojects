switch (mode) {
#ifdef HAVE_COOKED
	case GAMEPORT_MODE_COOKED:
		return 0;
#endif
	case GAMEPORT_MODE_RAW:
		return 0;
	default:
		return -1;
	}
