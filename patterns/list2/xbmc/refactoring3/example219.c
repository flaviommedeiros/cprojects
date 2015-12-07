switch (ext) {
	case ASAP_EXT('S', 'A', 'P'):
#ifndef ASAP_ONLY_SAP
	case ASAP_EXT('C', 'M', 'C'):
	case ASAP_EXT('C', 'M', '3'):
	case ASAP_EXT('C', 'M', 'R'):
	case ASAP_EXT('C', 'M', 'S'):
	case ASAP_EXT('D', 'M', 'C'):
	case ASAP_EXT('D', 'L', 'T'):
	case ASAP_EXT('M', 'P', 'T'):
	case ASAP_EXT('M', 'P', 'D'):
	case ASAP_EXT('R', 'M', 'T'):
	case ASAP_EXT('T', 'M', 'C'):
	case ASAP_EXT('T', 'M', '8'):
	case ASAP_EXT('T', 'M', '2'):
#endif
		return TRUE;
	default:
		return FALSE;
	}
