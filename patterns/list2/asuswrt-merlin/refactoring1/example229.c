if (r) {
		pthread_mutex_lock(&ctx->flying_transfers_lock);
		list_del(&itransfer->list);
		pthread_mutex_unlock(&ctx->flying_transfers_lock);
	}
#ifdef USBI_TIMERFD_AVAILABLE
	else if (first && usbi_using_timerfd(ctx)) {
		/* if this transfer has the lowest timeout of all active transfers,
		 * rearm the timerfd with this transfer's timeout */
		const struct itimerspec it = { {0, 0},
			{ itransfer->timeout.tv_sec, itransfer->timeout.tv_usec * 1000 } };
		usbi_dbg("arm timerfd for timeout in %dms (first in line)", transfer->timeout);
		r = timerfd_settime(ctx->timerfd, TFD_TIMER_ABSTIME, &it, NULL);
		if (r < 0)
			r = LIBUSB_ERROR_OTHER;
	}
#endif
