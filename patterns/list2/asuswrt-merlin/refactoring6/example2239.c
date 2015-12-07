if (!fix_fd(fd) ||
#if defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DONT)
      setsockopt(fd, IPPROTO_IP, IP_MTU_DISCOVER, &mtu, sizeof(mtu)) == -1 ||
#endif
#if defined(IP_TOS) && defined(IPTOS_CLASS_CS6)
      setsockopt(fd, IPPROTO_IP, IP_TOS, &tos, sizeof(tos)) == -1 ||
#endif
#if defined(HAVE_LINUX_NETWORK)
      setsockopt(fd, IPPROTO_IP, IP_PKTINFO, &oneopt, sizeof(oneopt)) == -1 ||
#else
      setsockopt(fd, IPPROTO_IP, IP_RECVIF, &oneopt, sizeof(oneopt)) == -1 ||
#endif
      setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &oneopt, sizeof(oneopt)) == -1)  
    die(_("failed to set options on DHCP socket: %s"), NULL, EC_BADNET);
