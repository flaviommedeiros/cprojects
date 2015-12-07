if (!pj_list_empty(&key->write_list)
#if defined(PJ_HAS_TCP) && PJ_HAS_TCP != 0
	    || key->connecting
#endif
	   )
	{
	    pj_assert(PJ_FD_ISSET(key->fd, wfdset));
	}
	else {
	    pj_assert(PJ_FD_ISSET(key->fd, wfdset) == 0);
	}
