switch (edata->saved_errno)
	{
			/* Loss of connection */
		case EPIPE:
#ifdef ECONNRESET
		case ECONNRESET:
#endif
			edata->sqlerrcode = ERRCODE_CONNECTION_FAILURE;
			break;

			/* All else is classified as internal errors */
		default:
			edata->sqlerrcode = ERRCODE_INTERNAL_ERROR;
			break;
	}
