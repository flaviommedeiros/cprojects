if ((listener->fd < 0)
#ifdef WITH_DETAIL
#ifndef WITH_DETAIL_THREAD
	    && (listener->type != RAD_LISTEN_DETAIL)
#endif
#endif
		) {
		char buffer[256];

		listener->print(listener, buffer, sizeof(buffer));
		ERROR("FATAL: Asked to read from closed socket: %s",
		       buffer);

		rad_panic("Socket was closed on us!");
		fr_exit_now(1);
	}
