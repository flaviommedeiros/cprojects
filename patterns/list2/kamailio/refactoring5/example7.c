#ifdef USE_FIFO
if (s_c->p_proto==P_FIFO)
			bytes_processed=fifo_process((char*)r->proc, (int)(r->end-r->proc),
										&bytes_needed, &sh, &s_c->saved_state);
		else
#endif
			bytes_processed=process_rpc_req(r->proc, (int)(r->end-r->proc),
										&bytes_needed, &sh, &s_c->saved_state);
