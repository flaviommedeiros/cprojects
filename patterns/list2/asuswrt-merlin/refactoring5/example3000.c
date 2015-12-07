#ifdef WIN32
if (bufferevent_async_can_connect(bev)) {
			bufferevent_setfd(bev, fd);
			r = bufferevent_async_connect(bev, fd, sa, socklen);
			if (r < 0)
				goto freesock;
			bufev_p->connecting = 1;
			result = 0;
			goto done;
		} else
#endif
		r = evutil_socket_connect(&fd, sa, socklen);
