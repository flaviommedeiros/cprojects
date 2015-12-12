#ifdef HAVE_SOLARIS
if (isatm) {
		/*
		** Have to turn on some special ATM promiscuous mode
		** for SunATM.
		** Do *NOT* turn regular promiscuous mode on; it doesn't
		** help, and may break things.
		*/
		if (strioctl(p->fd, A_PROMISCON_REQ, 0, NULL) < 0) {
			status = PCAP_ERROR;
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
			    "A_PROMISCON_REQ: %s", pcap_strerror(errno));
			goto bad;
		}
	} else
#endif
	if (p->opt.promisc) {
		/*
		** Enable promiscuous (not necessary on send FD)
		*/
		retv = dlpromiscon(p, DL_PROMISC_PHYS);
		if (retv < 0) {
			if (retv == PCAP_ERROR_PERM_DENIED)
				status = PCAP_ERROR_PROMISC_PERM_DENIED;
			else
				status = retv;
			goto bad;
		}

		/*
		** Try to enable multicast (you would have thought
		** promiscuous would be sufficient). (Skip if using
		** HP-UX or SINIX) (Not necessary on send FD)
		*/
#if !defined(__hpux) && !defined(sinix)
		retv = dlpromiscon(p, DL_PROMISC_MULTI);
		if (retv < 0)
			status = PCAP_WARNING;
#endif
	}
