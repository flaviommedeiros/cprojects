if (cmsgptr->cmsg_level == IPPROTO_IPV6
		 && (cmsgptr->cmsg_type == IPV6_PKTINFO
#if defined(IPV6_2292PKTINFO) && defined(IPV6_RECVPKTINFO)
            		 || cmsgptr->cmsg_type == IPV6_2292PKTINFO
#endif
		)) {
			const int IPI6_ADDR_OFF = offsetof(struct in6_pktinfo, ipi6_addr);
			to->sa_family = AF_INET6;
			/*#  define pktinfo(cmsgptr) ( (struct in6_pktinfo*)(CMSG_DATA(cmsgptr)) )*/
			/*to6->sin6_addr = pktinfo(cmsgptr)->ipi6_addr; - may be unaligned */
			memcpy(&to6->sin6_addr, (char*)(CMSG_DATA(cmsgptr)) + IPI6_ADDR_OFF, sizeof(to6->sin6_addr));
			/*to6->sin6_port = 123; */
			break;
		}
