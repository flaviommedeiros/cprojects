if (!pj_list_empty(&key->read_list)
#if defined(PJ_HAS_TCP) && PJ_HAS_TCP != 0
	    || !pj_list_empty(&key->accept_list)
#endif
	    ) 
	{
	    pj_assert(PJ_FD_ISSET(key->fd, rfdset));
	} 
	else {
	    pj_assert(PJ_FD_ISSET(key->fd, rfdset) == 0);
	}
