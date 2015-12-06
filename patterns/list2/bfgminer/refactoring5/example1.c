#ifdef HAVE_EPOLL
if (epollfd != -1)
		{
			if ((!watching_work_restart) && remaining_ms > 100)
				remaining_ms = 100;
			ret = epoll_wait(epollfd, evr, 2, remaining_ms);
			timer_set_now(tvp_now);
			switch (ret)
			{
				case -1:
					if (unlikely(errno != EINTR))
						return_via(out, rv = ICA_GETS_ERROR);
					ret = 0;
					break;
				case 0:  // timeout
					// handled after switch
					break;
				case 1:
					if (evr[0].data.fd != fd)  // must be work restart notifier
					{
						notifier_read(thr->work_restart_notifier);
						ret = 0;
						break;
					}
					// fallthru to...
				case 2:  // device has data
					ret = read(fd, buf, read_size);
					break;
				default:
					return_via(out, rv = ICA_GETS_ERROR);
			}
		}
		else
#endif
		{
			if (remaining_ms > 100)
				remaining_ms = 100;
			else
			if (remaining_ms < 1)
				remaining_ms = 1;
			vcom_set_timeout_ms(fd, remaining_ms);
			// Read first byte alone to get earliest tv_finish
			ret = read(fd, buf, first ? 1 : read_size);
			timer_set_now(tvp_now);
		}
