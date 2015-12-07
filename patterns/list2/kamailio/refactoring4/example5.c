#if defined(HAVE_SELECT) && defined(BLOCKING_USE_SELECT)
if (FD_ISSET(fd, &sel_set))
#else
		if (pf.revents&(POLLERR|POLLHUP|POLLNVAL)){ 
			LM_ERR("%s: poll error: flags %x\n",
					su2a((union sockaddr_union*)servaddr, addrlen),
					pf.revents);
			poll_err=1;
		}
