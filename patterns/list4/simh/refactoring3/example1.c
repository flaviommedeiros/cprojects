switch (dev->eth_api) {
#ifdef HAVE_PCAP_NETWORK
      case ETH_API_PCAP:
        status = pcap_dispatch ((pcap_t*)dev->handle, -1, &_eth_callback, (u_char*)dev);
        break;
#endif
#ifdef HAVE_TAP_NETWORK
      case ETH_API_TAP:
        if (1) {
          struct pcap_pkthdr header;
          int len;
          u_char buf[ETH_MAX_JUMBO_FRAME];

          memset(&header, 0, sizeof(header));
          len = read(dev->fd_handle, buf, sizeof(buf));
          if (len > 0) {
            status = 1;
            header.caplen = header.len = len;
            _eth_callback((u_char *)dev, &header, buf);
            }
          else {
            if (len < 0)
              status = -1;
            else
              status = 0;
            }
          }
        break;
#endif /* HAVE_TAP_NETWORK */
#ifdef HAVE_VDE_NETWORK
      case ETH_API_VDE:
        if (1) {
          struct pcap_pkthdr header;
          int len;
          u_char buf[ETH_MAX_JUMBO_FRAME];

          memset(&header, 0, sizeof(header));
          len = vde_recv((VDECONN *)dev->handle, buf, sizeof(buf), 0);
          if (len > 0) {
            status = 1;
            header.caplen = header.len = len;
            _eth_callback((u_char *)dev, &header, buf);
            }
          else {
            if (len < 0)
              status = -1;
            else
              status = 0;
            }
          }
        break;
#endif /* HAVE_VDE_NETWORK */
#ifdef HAVE_SLIRP_NETWORK
      case ETH_API_NAT:
        sim_slirp_dispatch ((SLIRP*)dev->handle);
        status = 1;
        break;
#endif /* HAVE_SLIRP_NETWORK */
      case ETH_API_UDP:
        if (1) {
          struct pcap_pkthdr header;
          int len;
          u_char buf[ETH_MAX_JUMBO_FRAME];

          memset(&header, 0, sizeof(header));
          len = (int)sim_read_sock (select_fd, (char *)buf, (int32)sizeof(buf));
          if (len > 0) {
            status = 1;
            header.caplen = header.len = len;
            _eth_callback((u_char *)dev, &header, buf);
            }
          else {
            if (len < 0)
              status = -1;
            else
              status = 0;
            }
          }
        break;
      }
