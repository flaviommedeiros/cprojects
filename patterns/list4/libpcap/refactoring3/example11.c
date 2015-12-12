switch (handlep->tp_version) {

	case TPACKET_V1:
	case TPACKET_V1_64:
#ifdef HAVE_TPACKET2
	case TPACKET_V2:
#endif
		/* Note that with large snapshot length (say 64K, which is
		 * the default for recent versions of tcpdump, the value that
		 * "-s 0" has given for a long time with tcpdump, and the
		 * default in Wireshark/TShark/dumpcap), if we use the snapshot
		 * length to calculate the frame length, only a few frames
		 * will be available in the ring even with pretty
		 * large ring size (and a lot of memory will be unused).
		 *
		 * Ideally, we should choose a frame length based on the
		 * minimum of the specified snapshot length and the maximum
		 * packet size.  That's not as easy as it sounds; consider,
		 * for example, an 802.11 interface in monitor mode, where
		 * the frame would include a radiotap header, where the
		 * maximum radiotap header length is device-dependent.
		 *
		 * So, for now, we just do this for Ethernet devices, where
		 * there's no metadata header, and the link-layer header is
		 * fixed length.  We can get the maximum packet size by
		 * adding 18, the Ethernet header length plus the CRC length
		 * (just in case we happen to get the CRC in the packet), to
		 * the MTU of the interface; we fetch the MTU in the hopes
		 * that it reflects support for jumbo frames.  (Even if the
		 * interface is just being used for passive snooping, the
		 * driver might set the size of buffers in the receive ring
		 * based on the MTU, so that the MTU limits the maximum size
		 * of packets that we can receive.)
		 *
		 * We don't do that if segmentation/fragmentation or receive
		 * offload are enabled, so we don't get rudely surprised by
		 * "packets" bigger than the MTU. */
		frame_size = handle->snapshot;
		if (handle->linktype == DLT_EN10MB) {
			int mtu;
			int offload;

			offload = iface_get_offload(handle);
			if (offload == -1) {
				*status = PCAP_ERROR;
				return -1;
			}
			if (!offload) {
				mtu = iface_get_mtu(handle->fd, handle->opt.source,
				    handle->errbuf);
				if (mtu == -1) {
					*status = PCAP_ERROR;
					return -1;
				}
				if (frame_size > mtu + 18)
					frame_size = mtu + 18;
			}
		}

		/* NOTE: calculus matching those in tpacket_rcv()
		 * in linux-2.6/net/packet/af_packet.c
		 */
		len = sizeof(sk_type);
		if (getsockopt(handle->fd, SOL_SOCKET, SO_TYPE, &sk_type,
		    &len) < 0) {
			pcap_snprintf(handle->errbuf, PCAP_ERRBUF_SIZE,
			    "getsockopt: %s", pcap_strerror(errno));
			*status = PCAP_ERROR;
			return -1;
		}
#ifdef PACKET_RESERVE
		len = sizeof(tp_reserve);
		if (getsockopt(handle->fd, SOL_PACKET, PACKET_RESERVE,
		    &tp_reserve, &len) < 0) {
			if (errno != ENOPROTOOPT) {
				/*
				 * ENOPROTOOPT means "kernel doesn't support
				 * PACKET_RESERVE", in which case we fall back
				 * as best we can.
				 */
				pcap_snprintf(handle->errbuf, PCAP_ERRBUF_SIZE,
				    "getsockopt: %s", pcap_strerror(errno));
				*status = PCAP_ERROR;
				return -1;
			}
			tp_reserve = 0;	/* older kernel, reserve not supported */
		}
#else
		tp_reserve = 0;	/* older kernel, reserve not supported */
#endif
		maclen = (sk_type == SOCK_DGRAM) ? 0 : MAX_LINKHEADER_SIZE;
			/* XXX: in the kernel maclen is calculated from
			 * LL_ALLOCATED_SPACE(dev) and vnet_hdr.hdr_len
			 * in:  packet_snd()           in linux-2.6/net/packet/af_packet.c
			 * then packet_alloc_skb()     in linux-2.6/net/packet/af_packet.c
			 * then sock_alloc_send_pskb() in linux-2.6/net/core/sock.c
			 * but I see no way to get those sizes in userspace,
			 * like for instance with an ifreq ioctl();
			 * the best thing I've found so far is MAX_HEADER in
			 * the kernel part of linux-2.6/include/linux/netdevice.h
			 * which goes up to 128+48=176; since pcap-linux.c
			 * defines a MAX_LINKHEADER_SIZE of 256 which is
			 * greater than that, let's use it.. maybe is it even
			 * large enough to directly replace macoff..
			 */
		tp_hdrlen = TPACKET_ALIGN(handlep->tp_hdrlen) + sizeof(struct sockaddr_ll) ;
		netoff = TPACKET_ALIGN(tp_hdrlen + (maclen < 16 ? 16 : maclen)) + tp_reserve;
			/* NOTE: AFAICS tp_reserve may break the TPACKET_ALIGN
			 * of netoff, which contradicts
			 * linux-2.6/Documentation/networking/packet_mmap.txt
			 * documenting that:
			 * "- Gap, chosen so that packet data (Start+tp_net)
			 * aligns to TPACKET_ALIGNMENT=16"
			 */
			/* NOTE: in linux-2.6/include/linux/skbuff.h:
			 * "CPUs often take a performance hit
			 *  when accessing unaligned memory locations"
			 */
		macoff = netoff - maclen;
		req.tp_frame_size = TPACKET_ALIGN(macoff + frame_size);
		req.tp_frame_nr = handle->opt.buffer_size/req.tp_frame_size;
		break;

#ifdef HAVE_TPACKET3
	case TPACKET_V3:
		/* The "frames" for this are actually buffers that
		 * contain multiple variable-sized frames.
		 *
		 * We pick a "frame" size of 128K to leave enough
		 * room for at least one reasonably-sized packet
		 * in the "frame". */
		req.tp_frame_size = MAXIMUM_SNAPLEN;
		req.tp_frame_nr = handle->opt.buffer_size/req.tp_frame_size;
		break;
#endif
	default:
		pcap_snprintf(handle->errbuf, PCAP_ERRBUF_SIZE,
		    "Internal error: unknown TPACKET_ value %u",
		    handlep->tp_version);
		*status = PCAP_ERROR;
		return -1;
	}
