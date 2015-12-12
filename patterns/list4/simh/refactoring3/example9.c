switch (dev->eth_api) {
#ifdef HAVE_PCAP_NETWORK
    case ETH_API_PCAP:
      status = pcap_sendpacket((pcap_t*)dev->handle, (u_char*)packet->msg, packet->len);
      break;
#endif
#ifdef HAVE_TAP_NETWORK
    case ETH_API_TAP:
      status = (((int)packet->len == write(dev->fd_handle, (void *)packet->msg, packet->len)) ? 0 : -1);
      break;
#endif
#ifdef HAVE_VDE_NETWORK
    case ETH_API_VDE:
      status = vde_send((VDECONN*)dev->handle, (void *)packet->msg, packet->len, 0);
      if ((status == (int)packet->len) || (status == 0))
        status = 0;
      else
        if ((status == -1) && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
          status = 0;
        else
          status = 1;
      break;
#endif
#ifdef HAVE_SLIRP_NETWORK
    case ETH_API_NAT:
      status = sim_slirp_send((SLIRP*)dev->handle, (char *)packet->msg, (size_t)packet->len, 0);
      if ((status == (int)packet->len) || (status == 0))
        status = 0;
      else
        status = 1;
      break;
#endif
    case ETH_API_UDP:
      status = (((int32)packet->len == sim_write_sock (dev->fd_handle, (char *)packet->msg, (int32)packet->len)) ? 0 : -1);
      break;
    }
