#ifdef UPNP_STRICT
if(h->req_SIDOff <= 0 || h->req_SIDLen == 0) {
		/* SID: header missing or empty */
		BuildResp2_upnphttp(h, 412, "Precondition Failed", 0, 0);
	} else if(h->req_CallbackOff > 0 || h->req_NTOff > 0) {
		/* no NT: or Callback: header must be present */
		BuildResp2_upnphttp(h, 400, "Incompatible header fields", 0, 0);
	} else
#endif
	if(upnpevents_removeSubscriber(h->req_buf + h->req_SIDOff, h->req_SIDLen) < 0) {
		BuildResp2_upnphttp(h, 412, "Precondition Failed", 0, 0);
	} else {
		BuildResp_upnphttp(h, 0, 0);
	}
