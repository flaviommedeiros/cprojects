#ifndef NO_ONREPLY_ROUTE_ERROR
if (unlikely(ret<0)){
				LM_WARN("error while trying onreply script\n");
				goto error_rpl;
			}else
#endif /* NO_ONREPLY_ROUTE_ERROR */
			if (unlikely(ret==0 || (ctx.run_flags&DROP_R_F))){
				STATS_RPL_FWD_DROP();
				goto skip_send_reply; /* drop the message, no error */
			}
