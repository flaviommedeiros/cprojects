#ifdef PCAP_RAW_SOCKETS
if (sock->lsock.pcap) {
		/* set ethernet destination address to DHCP-Client-Hardware-Address in request. */
		uint8_t dhmac[ETHER_HDR_LEN] = { 0 };
		bool found = false;
		VALUE_PAIR *vp;
		if ((vp = fr_pair_find_by_num(request->packet->vps, DHCP_MAGIC_VENDOR, 267, TAG_ANY))) {
			if (vp->data.length == sizeof(vp->vp_ether)) {
				memcpy(dhmac, vp->vp_ether, vp->data.length);
				found = true;
			}
		}

		if (!found) {
			REDEBUG("&DHCP-Client-Hardware-Address not found in request");
			return -1;
		}

		return fr_dhcp_send_pcap(sock->lsock.pcap, dhmac, request->reply);
	} else
#endif
	{
		return fr_dhcp_send_socket(request->reply);
	}
