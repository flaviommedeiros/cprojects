#ifdef USE_FIFO
if (cs->p_proto==P_FIFO)
		fifo_process((char*)buf, bytes, &bytes_needed, &sh, &saved_state);
	else
#endif
		process_rpc_req(buf, bytes, &bytes_needed, &sh, &saved_state);
