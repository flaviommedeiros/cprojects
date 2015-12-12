#ifdef SO_BROADCAST
if (setsockopt (udp_fd, SOL_SOCKET, SO_BROADCAST, &(s->is_broadcast), sizeof(s->is_broadcast)) != 0)
#endif
           goto fail;
