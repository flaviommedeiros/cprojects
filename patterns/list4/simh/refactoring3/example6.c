switch (eth_api) {
#ifdef HAVE_PCAP_NETWORK
  case ETH_API_PCAP:
    pcap_close(pcap);
    break;
#endif
#ifdef HAVE_TAP_NETWORK
  case ETH_API_TAP:
    close(pcap_fd);
    break;
#endif
#ifdef HAVE_VDE_NETWORK
  case ETH_API_VDE:
    vde_close((VDECONN*)pcap);
    break;
#endif
#ifdef HAVE_SLIRP_NETWORK
  case ETH_API_NAT:
    sim_slirp_close((SLIRP*)pcap);
    break;
#endif
  case ETH_API_UDP:
    sim_close_sock(pcap_fd);
    break;
  }
