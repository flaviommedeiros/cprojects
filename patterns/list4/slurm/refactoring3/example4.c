switch (*state) {
		case RM_PARTITION_FREE:
			*state = BG_BLOCK_FREE;
			break;
		case RM_PARTITION_CONFIGURING:
			*state = BG_BLOCK_BOOTING;
			break;
#ifdef HAVE_BGL
		case RM_PARTITION_BUSY:
			*state = BG_BLOCK_BUSY;
			break;
#else
		case RM_PARTITION_REBOOTING:
			*state = BG_BLOCK_REBOOTING;
			break;
#endif
		case RM_PARTITION_READY:
			*state = BG_BLOCK_INITED;
			break;
		case RM_PARTITION_DEALLOCATING:
			*state = BG_BLOCK_TERM;
			break;
		case RM_PARTITION_ERROR:
			*state = BG_BLOCK_ERROR_FLAG;
			break;
		case RM_PARTITION_NAV:
			*state = BG_BLOCK_NAV;
			break;
		default:
			break;
		}
