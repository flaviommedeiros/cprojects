if (!((inst->packet_code == 0) || (request->packet->code == inst->packet_code) ||
	      (request->reply->code == inst->packet_code)
#ifdef WITH_PROXY
	      || (request->proxy && (request->proxy->code == inst->packet_code)) ||
	      (request->proxy_reply && (request->proxy_reply->code == inst->packet_code))
#endif
		    )) {
		RDEBUG2("Packet type is not %s. Not executing.", inst->packet_type);

		return RLM_MODULE_NOOP;
	}
