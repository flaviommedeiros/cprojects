if (cmsg != NULL
	  && CMSG_NXTHDR (&mesg, cmsg) == NULL
#ifdef IP_PKTINFO
	  && cmsg->cmsg_level == SOL_IP 
	  && cmsg->cmsg_type == IP_PKTINFO
#elif defined(IP_RECVDSTADDR)
	  && cmsg->cmsg_level == IPPROTO_IP
	  && cmsg->cmsg_type == IP_RECVDSTADDR
#else
#error ENABLE_IP_PKTINFO is set without IP_PKTINFO xor IP_RECVDSTADDR (fix syshead.h)
#endif
	  && cmsg->cmsg_len >= sizeof (struct openvpn_in4_pktinfo))
	{
#ifdef IP_PKTINFO
	  struct in_pktinfo *pkti = (struct in_pktinfo *) CMSG_DATA (cmsg);
	  from->pi.in4.ipi_ifindex = pkti->ipi_ifindex;
	  from->pi.in4.ipi_spec_dst = pkti->ipi_spec_dst;
#elif defined(IP_RECVDSTADDR)
	  from->pi.in4 = *(struct in_addr*) CMSG_DATA (cmsg);
#else
#error ENABLE_IP_PKTINFO is set without IP_PKTINFO xor IP_RECVDSTADDR (fix syshead.h)
#endif
	}
      else if (cmsg != NULL
	  && CMSG_NXTHDR (&mesg, cmsg) == NULL
	  && cmsg->cmsg_level == IPPROTO_IPV6 
	  && cmsg->cmsg_type == IPV6_PKTINFO
	  && cmsg->cmsg_len >= sizeof (struct openvpn_in6_pktinfo))
	{
	  struct in6_pktinfo *pkti6 = (struct in6_pktinfo *) CMSG_DATA (cmsg);
	  from->pi.in6.ipi6_ifindex = pkti6->ipi6_ifindex;
	  from->pi.in6.ipi6_addr = pkti6->ipi6_addr;
	}
