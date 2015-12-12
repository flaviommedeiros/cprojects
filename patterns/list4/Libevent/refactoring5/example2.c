#ifdef _WIN32
if (bufferevent_async_can_connect_(bev)) {
			bufferevent_setfd(bev, fd);
			r = bufferevent_async_connect_(bev, fd, sa, socklen);
			if (r < 0)
				goto freesock;
			bufev_p->connecting = 1;
			result = 0;
			goto done;
		} else
#endif
		r = evutil_socket_connect_(&fd, sa, socklen);
