switch (stat->data_type) {
	  case KSTAT_DATA_INT32:
	    sockid = stat->value.i32;
	    break;
	  case KSTAT_DATA_UINT32:
	    sockid = stat->value.ui32;
	    break;
#ifdef _INT64_TYPE
	  case KSTAT_DATA_UINT64:
	    sockid = stat->value.ui64;
	    break;
	  case KSTAT_DATA_INT64:
	    sockid = stat->value.i64;
	    break;
#endif
	  default:
	    fprintf(stderr, "chip_id type %d unknown\n", stat->data_type);
	    look_chips = 0;
	    continue;
	}
