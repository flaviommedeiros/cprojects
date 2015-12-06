#ifdef WITH_ACCOUNTING
if (listener->type != RAD_LISTEN_DETAIL)
#endif
	{
		sock = listener->data;
		sock->last_packet = now.tv_sec;

#ifdef WITH_TCP
		packet->proto = sock->proto;
#endif
	}
