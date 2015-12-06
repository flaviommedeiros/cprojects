switch (cast) {
#ifdef WITH_ASCEND_BINARY
	case PW_TYPE_ABINARY:
#endif
	case PW_TYPE_COMBO_IP_ADDR:
	case PW_TYPE_TLV:
	case PW_TYPE_EXTENDED:
	case PW_TYPE_LONG_EXTENDED:
	case PW_TYPE_EVS:
	case PW_TYPE_VSA:
		*error = "Forbidden data type in cast";
		return -(p - start);

	default:
		break;
	}
