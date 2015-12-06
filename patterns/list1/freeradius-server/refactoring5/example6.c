#ifdef WITH_COA
if (((request->proxy->code == PW_CODE_COA_REQUEST) ||
		     (request->proxy->code == PW_CODE_DISCONNECT_REQUEST)) &&
		    (request->packet->code != request->proxy->code)) {
			when.tv_sec += request->home_server->coa_mrd;
		} else
#endif
			timeradd(&when, request_response_window(request), &when);
