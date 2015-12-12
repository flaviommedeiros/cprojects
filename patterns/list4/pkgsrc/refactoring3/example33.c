switch (h_error) {
		case HOST_NOT_FOUND:
		case NO_DATA:
			error = EAI_NODATA;
			break;
		case TRY_AGAIN:
			error = EAI_AGAIN;
			break;
		case NO_RECOVERY:
#ifdef NETDB_INTERNAL
		case NETDB_INTERNAL:
#endif
		default:
			error = EAI_FAIL;
			break;
		}
