#if LWS_POSIX
if (pa.prev_events != pa.events)
#endif
	{
		
		if (lws_plat_change_pollfd(context, wsi, pfd)) {
			lwsl_info("%s failed\n", __func__);
			return 1;
		}

		sampled_tid = context->service_tid;
		if (sampled_tid) {
			tid = context->protocols[0].callback(context, NULL,
				     LWS_CALLBACK_GET_THREAD_ID, NULL, NULL, 0);
			if (tid == -1)
				return -1;
			if (tid != sampled_tid)
				lws_cancel_service(context);
		}
	}
