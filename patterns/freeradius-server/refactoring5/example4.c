#ifdef WITH_PROXY
if (request->proxy_reply && (!request->reply || !request->reply->code)) {
			code = request->proxy_reply->code;
		} else
#endif
		if (request->reply) {
			code = request->reply->code;
		}
