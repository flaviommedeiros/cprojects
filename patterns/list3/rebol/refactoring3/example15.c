switch (result) {

	case 0: // no error
	case NE_ISCONN:
		// Connected, set state:
		CLR_FLAG(sock->state, RSM_ATTEMPT);
		SET_FLAG(sock->state, RSM_CONNECT);
		Get_Local_IP(sock);
		Signal_Device(sock, EVT_CONNECT);
		return DR_DONE; // done

#ifdef TO_WIN32
	case NE_INVALID:	// Corrects for Microsoft bug
#endif
	case NE_WOULDBLOCK:
	case NE_INPROGRESS:
	case NE_ALREADY:
		// Still trying:
		SET_FLAG(sock->state, RSM_ATTEMPT);
		return DR_PEND;

	default:
		// An error happened:
		CLR_FLAG(sock->state, RSM_ATTEMPT);
		sock->error = result;
		//Signal_Device(sock, EVT_ERROR);
		return DR_ERROR;
	}
