if (
#ifdef ETIMEDOUT
		(sys_errno == ETIMEDOUT) ||
#endif
		(sys_errno == EINPROGRESS) ||
		(sys_errno == EALREADY) ||
		(sys_errno == EAGAIN)) {

		/*
		 * retry
		 */

		if (state->wait_nsec < 250000) {
			state->wait_nsec *= 1.5;
		}

		subreq = async_connect_send(state, state->ev, state->fd,
					    (struct sockaddr *)&state->ss,
					    state->salen);
		if (tevent_req_nomem(subreq, req)) {
			return;
		}
		if (!tevent_req_set_endtime(
			    subreq, state->ev,
			    timeval_current_ofs(0, state->wait_nsec))) {
			tevent_req_nterror(req, NT_STATUS_NO_MEMORY);
			return;
		}
		tevent_req_set_callback(subreq, open_socket_out_connected, req);
		return;
	}
