switch (pcap->type) {
	case PCAP_INTERFACE_OUT:
	case PCAP_INTERFACE_IN:
	case PCAP_INTERFACE_IN_OUT:
	{
#if defined(HAVE_PCAP_CREATE) && defined(HAVE_PCAP_ACTIVATE)
		pcap->handle = pcap_create(pcap->name, pcap->errbuf);
		if (!pcap->handle) {
			fr_strerror_printf("%s", pcap->errbuf);
			return -1;
		}
		if (pcap_set_snaplen(pcap->handle, SNAPLEN) != 0) {
		create_error:
			fr_strerror_printf("%s", pcap_geterr(pcap->handle));
			pcap_close(pcap->handle);
			pcap->handle = NULL;
			return -1;
		}
		if (pcap_set_timeout(pcap->handle, PCAP_NONBLOCK_TIMEOUT) != 0) {
			goto create_error;
		}
		if (pcap_set_promisc(pcap->handle, pcap->promiscuous) != 0) {
			goto create_error;
		}

		if (pcap_set_buffer_size(pcap->handle, SNAPLEN *
					 (pcap->buffer_pkts ? pcap->buffer_pkts : PCAP_BUFFER_DEFAULT)) != 0) {
			goto create_error;
		}
		if (pcap_activate(pcap->handle) != 0) {
			goto create_error;
		}
#else
		/*
		 *	Alternative functions for libpcap < 1.0
		 */
		pcap->handle = pcap_open_live(pcap->name, SNAPLEN, pcap->promiscuous, PCAP_NONBLOCK_TIMEOUT,
					      pcap->errbuf);
		if (!pcap->handle) {
			fr_strerror_printf("%s", pcap->errbuf);
			return -1;
		}
#endif

		/*
		 *	Do this later so we get real errors.
		 */
		if (fr_pcap_mac_addr((uint8_t *)&pcap->ether_addr, pcap->name) != 0) {
			fr_strerror_printf("Couldn't get MAC address for interface %s", pcap->name);
			pcap_close(pcap->handle);
			return -1;
		}

		/*
		 *	Despite accepting an errbuff, pcap_setnonblock doesn't seem to write
		 *	error message there in newer versions.
		 */
		if (pcap_setnonblock(pcap->handle, true, pcap->errbuf) != 0) {
			fr_strerror_printf("%s", *pcap->errbuf != '\0' ?
					   pcap->errbuf : pcap_geterr(pcap->handle));
			pcap_close(pcap->handle);
			pcap->handle = NULL;
			return -1;
		}

		pcap->fd = pcap_get_selectable_fd(pcap->handle);
		pcap->link_layer = pcap_datalink(pcap->handle);
#ifndef __linux__
		{
			int value = 1;
			if (ioctl(pcap->fd, BIOCIMMEDIATE, &value) < 0) {
				fr_strerror_printf("Failed setting BIOCIMMEDIATE: %s", fr_syserror(errno));
			}
		}
#endif
	}
		break;

	case PCAP_FILE_IN:
		pcap->handle = pcap_open_offline(pcap->name, pcap->errbuf);
		if (!pcap->handle) {
			fr_strerror_printf("%s", pcap->errbuf);

			return -1;
		}
		pcap->fd = pcap_get_selectable_fd(pcap->handle);
		pcap->link_layer = pcap_datalink(pcap->handle);
		break;

	case PCAP_FILE_OUT:
		if (pcap->link_layer < 0) {
			pcap->link_layer = DLT_EN10MB;
		}
		pcap->handle = pcap_open_dead(pcap->link_layer, SNAPLEN);
		if (!pcap->handle) {
			fr_strerror_printf("Unknown error occurred opening dead PCAP handle");

			return -1;
		}
		pcap->dumper = pcap_dump_open(pcap->handle, pcap->name);
		if (!pcap->dumper) {
			fr_strerror_printf("%s", pcap_geterr(pcap->handle));

			return -1;
		}
		break;

#ifdef HAVE_PCAP_FOPEN_OFFLINE
	case PCAP_STDIO_IN:
		pcap->handle = pcap_fopen_offline(stdin, pcap->errbuf);
		if (!pcap->handle) {
			fr_strerror_printf("%s", pcap->errbuf);

			return -1;
		}
		pcap->fd = pcap_get_selectable_fd(pcap->handle);
		pcap->link_layer = pcap_datalink(pcap->handle);
		break;
#else
	case PCAP_STDIO_IN:
		fr_strerror_printf("This version of libpcap does not support reading pcap data from streams");

		return -1;
#endif
#ifdef HAVE_PCAP_DUMP_FOPEN
	case PCAP_STDIO_OUT:
		pcap->handle = pcap_open_dead(DLT_EN10MB, SNAPLEN);
		pcap->dumper = pcap_dump_fopen(pcap->handle, stdout);
		if (!pcap->dumper) {
			fr_strerror_printf("%s", pcap_geterr(pcap->handle));

			return -1;
		}
		break;
#else
	case PCAP_STDIO_OUT:
		fr_strerror_printf("This version of libpcap does not support writing pcap data to streams");

		return -1;
#endif
	case PCAP_INVALID:
	default:
		fr_assert(0);
		fr_strerror_printf("Bad handle type (%i)", pcap->type);
		return -1;
	}
