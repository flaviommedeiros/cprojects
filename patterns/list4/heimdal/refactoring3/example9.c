switch(rta->rta_type){
	    case IFA_ADDRESS:
		ifamap.address = rtadata;
		ifamap.address_len = rtapayload;
		break;
	    case IFA_LOCAL:
		ifamap.local = rtadata;
		ifamap.local_len = rtapayload;
		break;
	    case IFA_BROADCAST:
		ifamap.broadcast = rtadata;
		ifamap.broadcast_len = rtapayload;
		break;
#ifdef HAVE_IFADDRS_IFA_ANYCAST
	    case IFA_ANYCAST:
		ifamap.anycast = rtadata;
		ifamap.anycast_len = rtapayload;
		break;
#endif
	    case IFA_LABEL:
	      if (!build)
		nlen += NLMSG_ALIGN(rtapayload + 1);
	      else{
		ifa->ifa_name = ifname;
		if (iflist[nlm_index] == NULL)
		  iflist[nlm_index] = ifname;
		strncpy(ifa->ifa_name, rtadata, rtapayload);
		ifa->ifa_name[rtapayload] = '\0';
		ifname += NLMSG_ALIGN(rtapayload + 1);
	      }
	      break;
	    case IFA_UNSPEC:
	      break;
	    case IFA_CACHEINFO:
	      break;
	    default:
	      break;
	    }
