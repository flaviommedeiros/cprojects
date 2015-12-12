#ifdef HAVE_SLIRP_NETWORK
if (dev->eth_api == ETH_API_NAT) {
        sel_ret = sim_slirp_select ((SLIRP*)dev->handle, 250);
        }
      else
#endif
        {
        fd_set setl;
        struct timeval timeout;
        
        FD_ZERO(&setl);
        FD_SET(select_fd, &setl);
        timeout.tv_sec = 0;
        timeout.tv_usec = 250*1000;
        sel_ret = select(1+select_fd, &setl, NULL, NULL, &timeout);
        }
