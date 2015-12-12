#ifdef HAVE_ZEROCOPY_BPF
if (pb->zerocopy) {
			if (p->buffer != NULL)
				pcap_ack_zbuf(p);
			i = pcap_next_zbuf(p, &cc);
			if (i == 0)
				goto again;
			if (i < 0)
				return (PCAP_ERROR);
		} else
#endif
		{
			cc = read(p->fd, p->buffer, p->bufsize);
		}
