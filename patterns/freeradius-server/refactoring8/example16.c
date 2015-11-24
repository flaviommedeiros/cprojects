static void rs_packet_process(uint64_t count, rs_event_t *event, struct pcap_pkthdr const *header, uint8_t const *data)
{
	rs_stats_t		*stats = event->stats;
	struct timeval		elapsed = {0, 0};
	struct timeval		latency;

	/*
	 *	Pointers into the packet data we just received
	 */
	ssize_t len;
	uint8_t const		*p = data;

	ip_header_t const	*ip = NULL;		/* The IP header */
	ip_header6_t const	*ip6 = NULL;		/* The IPv6 header */
	udp_header_t const	*udp;			/* The UDP header */
	uint8_t			version;		/* IP header version */
	bool			response;		/* Was it a response code */

	decode_fail_t		reason;			/* Why we failed decoding the packet */
	static uint64_t		captured = 0;

	rs_status_t		status = RS_NORMAL;	/* Any special conditions (RTX, Unlinked, ID-Reused) */
	RADIUS_PACKET		*current;		/* Current packet were processing */
	rs_request_t		*original = NULL;

	rs_request_t		search;

	memset(&search, 0, sizeof(search));

	if (!start_pcap.tv_sec) {
		start_pcap = header->ts;
	}

	if (RIDEBUG_ENABLED()) {
		rs_time_print(timestr, sizeof(timestr), &header->ts);
	}

	len = fr_link_layer_offset(data, header->caplen, event->in->link_layer);
	if (len < 0) {
		REDEBUG("Failed determining link layer header offset");
		return;
	}
	p += len;

	version = (p[0] & 0xf0) >> 4;
	switch (version) {
	case 4:
		ip = (ip_header_t const *)p;
		len = (0x0f & ip->ip_vhl) * 4;	/* ip_hl specifies length in 32bit words */
		p += len;
		break;

	case 6:
		ip6 = (ip_header6_t const *)p;
		p += sizeof(ip_header6_t);

		break;

	default:
		REDEBUG("IP version invalid %i", version);
		return;
	}

	/*
	 *	End of variable length bits, do basic check now to see if packet looks long enough
	 */
	len = (p - data) + sizeof(udp_header_t) + sizeof(radius_packet_t);	/* length value */
	if ((size_t) len > header->caplen) {
		REDEBUG("Packet too small, we require at least %zu bytes, captured %i bytes",
			(size_t) len, header->caplen);
		return;
	}

	/*
	 *	UDP header validation.
	 */
	udp = (udp_header_t const *)p;
	{
		uint16_t udp_len;
		ssize_t diff;

		udp_len = ntohs(udp->len);
		diff = udp_len - (header->caplen - (p - data));
		/* Truncated data */
		if (diff > 0) {
			REDEBUG("Packet too small by %zi bytes, UDP header + Payload should be %hu bytes",
				diff, udp_len);
			return;
		}

#if 0
		/*
		 *	It seems many probes add trailing garbage to the end
		 *	of each capture frame.  This has been observed with
		 *	the F5 and Netscout.
		 *
		 *	Leaving the code here in case it's ever needed for
		 *	debugging.
		 */
		else if (diff < 0) {
			REDEBUG("Packet too big by %zi bytes, UDP header + Payload should be %hu bytes",
				diff * -1, udp_len);
			return;
		}
#endif
	}
	if ((version == 4) && conf->verify_udp_checksum) {
		uint16_t expected;

		expected = fr_udp_checksum((uint8_t const *) udp, ntohs(udp->len), udp->checksum,
					   ip->ip_src, ip->ip_dst);
		if (udp->checksum != expected) {
			REDEBUG("UDP checksum invalid, packet: 0x%04hx calculated: 0x%04hx",
				ntohs(udp->checksum), ntohs(expected));
			/* Not a fatal error */
		}
	}
	p += sizeof(udp_header_t);

	/*
	 *	With artificial talloc memory limits there's a good chance we can
	 *	recover once some requests timeout, so make an effort to deal
	 *	with allocation failures gracefully.
	 */
	current = rad_alloc(conf, false);
	if (!current) {
		REDEBUG("Failed allocating memory to hold decoded packet");
		rs_tv_add_ms(&header->ts, conf->stats.timeout, &stats->quiet);
		return;
	}

	current->timestamp = header->ts;
	current->data_len = header->caplen - (p - data);
	memcpy(&current->data, &p, sizeof(current->data));

	/*
	 *	Populate IP/UDP fields from PCAP data
	 */
	if (ip) {
		current->src_ipaddr.af = AF_INET;
		current->src_ipaddr.ipaddr.ip4addr.s_addr = ip->ip_src.s_addr;

		current->dst_ipaddr.af = AF_INET;
		current->dst_ipaddr.ipaddr.ip4addr.s_addr = ip->ip_dst.s_addr;
	} else {
		current->src_ipaddr.af = AF_INET6;
		memcpy(current->src_ipaddr.ipaddr.ip6addr.s6_addr, ip6->ip_src.s6_addr,
		       sizeof(current->src_ipaddr.ipaddr.ip6addr.s6_addr));

		current->dst_ipaddr.af = AF_INET6;
		memcpy(current->dst_ipaddr.ipaddr.ip6addr.s6_addr, ip6->ip_dst.s6_addr,
		       sizeof(current->dst_ipaddr.ipaddr.ip6addr.s6_addr));
	}

	current->src_port = ntohs(udp->src);
	current->dst_port = ntohs(udp->dst);

	if (!rad_packet_ok(current, 0, &reason)) {
		REDEBUG("%s", fr_strerror());
		if (conf->event_flags & RS_ERROR) {
			rs_packet_print(NULL, count, RS_ERROR, event->in, current, &elapsed, NULL, false, false);
		}
		rad_free(&current);

		return;
	}

	switch (current->code) {
	case PW_CODE_ACCOUNTING_RESPONSE:
	case PW_CODE_ACCESS_REJECT:
	case PW_CODE_ACCESS_ACCEPT:
	case PW_CODE_ACCESS_CHALLENGE:
	case PW_CODE_COA_NAK:
	case PW_CODE_COA_ACK:
	case PW_CODE_DISCONNECT_NAK:
	case PW_CODE_DISCONNECT_ACK:
	case PW_CODE_STATUS_CLIENT:
	{
		/* look for a matching request and use it for decoding */
		search.expect = current;
		original = rbtree_finddata(request_tree, &search);

		/*
		 *	Verify this code is allowed
		 */
		if (conf->filter_response_code && (conf->filter_response_code != current->code)) {
			drop_response:
			RDEBUG2("Response dropped by filter");
			rad_free(&current);

			/* We now need to cleanup the original request too */
			if (original) {
				RS_CLEANUP_NOW(original, true);
			}
			return;
		}

		/*
		 *	Only decode attributes if we want to print them or filter on them
		 *	rad_packet_ok does checks to verify the packet is actually valid.
		 */
		if (conf->decode_attrs) {
			int ret;
			FILE *log_fp = fr_log_fp;

			fr_log_fp = NULL;
			ret = rad_decode(current, original ? original->expect : NULL, conf->radius_secret);
			fr_log_fp = log_fp;
			if (ret != 0) {
				rad_free(&current);
				REDEBUG("Failed decoding");
				return;
			}
		}

		/*
		 *	Check if we've managed to link it to a request
		 */
		if (original) {
			/*
			 *	Now verify the packet passes the attribute filter
			 */
			if (conf->filter_response_vps) {
				fr_pair_list_sort(&current->vps, fr_pair_cmp_by_da_tag);
				if (!fr_pair_validate_relaxed(NULL, conf->filter_response_vps, current->vps)) {
					goto drop_response;
				}
			}

			/*
			 *	Is this a retransmission?
			 */
			if (original->linked) {
				status = RS_RTX;
				original->rt_rsp++;

				rad_free(&original->linked);
				fr_event_delete(event->list, &original->event);
			/*
			 *	...nope it's the first response to a request.
			 */
			} else {
				original->stats_rsp = &stats->exchange[current->code];
			}

			/*
			 *	Insert a callback to remove the request and response
			 *	from the tree after the timeout period.
			 *	The delay is so we can detect retransmissions.
			 */
			original->linked = talloc_steal(original, current);
			rs_tv_add_ms(&header->ts, conf->stats.timeout, &original->when);
			if (!fr_event_insert(event->list, _rs_event, original, &original->when,
					     &original->event)) {
				REDEBUG("Failed inserting new event");
				/*
				 *	Delete the original request/event, it's no longer valid
				 *	for statistics.
				 */
				talloc_free(original);
				return;
			}
		/*
		 *	No request seen, or request was dropped by attribute filter
		 */
		} else {
			/*
			 *	If conf->filter_request_vps are set assume the original request was dropped,
			 *	the alternative is maintaining another 'filter', but that adds
			 *	complexity, reduces max capture rate, and is generally a PITA.
			 */
			if (conf->filter_request) {
				rad_free(&current);
				RDEBUG2("Original request dropped by filter");
				return;
			}

			status = RS_UNLINKED;
			stats->exchange[current->code].interval.unlinked_total++;
		}

		rs_response_to_pcap(event, original, header, data);
		response = true;
		break;
	}

	case PW_CODE_ACCOUNTING_REQUEST:
	case PW_CODE_ACCESS_REQUEST:
	case PW_CODE_COA_REQUEST:
	case PW_CODE_DISCONNECT_REQUEST:
	case PW_CODE_STATUS_SERVER:
	{
		/*
		 *	Verify this code is allowed
		 */
		if (conf->filter_request_code && (conf->filter_request_code != current->code)) {
			drop_request:

			RDEBUG2("Request dropped by filter");
			rad_free(&current);

			return;
		}

		/*
		 *	Only decode attributes if we want to print them or filter on them
		 *	rad_packet_ok does checks to verify the packet is actually valid.
		 */
		if (conf->decode_attrs) {
			int ret;
			FILE *log_fp = fr_log_fp;

			fr_log_fp = NULL;
			ret = rad_decode(current, NULL, conf->radius_secret);
			fr_log_fp = log_fp;

			if (ret != 0) {
				rad_free(&current);
				REDEBUG("Failed decoding");
				return;
			}

			fr_pair_list_sort(&current->vps, fr_pair_cmp_by_da_tag);
		}

		/*
		 *	Save the request for later matching
		 */
		search.expect = rad_alloc_reply(current, current);
		if (!search.expect) {
			REDEBUG("Failed allocating memory to hold expected reply");
			rs_tv_add_ms(&header->ts, conf->stats.timeout, &stats->quiet);
			rad_free(&current);
			return;
		}
		search.expect->code = current->code;

		if ((conf->link_da_num > 0) && current->vps) {
			int ret;
			ret = rs_get_pairs(current, &search.link_vps, current->vps, conf->link_da,
					   conf->link_da_num);
			if (ret < 0) {
				ERROR("Failed extracting RTX linking pairs from request");
				rad_free(&current);
				return;
			}
		}

		/*
		 *	If we have linking attributes set, attempt to find a request in the linking tree.
		 */
		if (search.link_vps) {
			rs_request_t *tuple;

			original = rbtree_finddata(link_tree, &search);
			tuple = rbtree_finddata(request_tree, &search);

			/*
			 *	If the packet we matched using attributes is not the same
			 *	as the packet in the request tree, then we need to clean up
			 *	the packet in the request tree.
			 */
			if (tuple && (original != tuple)) {
				RS_CLEANUP_NOW(tuple, true);
			}
		/*
		 *	Detect duplicates using the normal 5-tuple of src/dst ips/ports id
		 */
		} else {
			original = rbtree_finddata(request_tree, &search);
			if (original && (memcmp(original->expect->vector, current->vector,
			    			sizeof(original->expect->vector)) != 0)) {
				/*
				 *	ID reused before the request timed out (which may be an issue)...
				 */
				if (!original->linked) {
					status = RS_REUSED;
					stats->exchange[current->code].interval.reused_total++;
					/* Occurs regularly downstream of proxy servers (so don't complain) */
					RS_CLEANUP_NOW(original, true);
				/*
				 *	...and before we saw a response (which may be a bigger issue).
				 */
				} else {
					RS_CLEANUP_NOW(original, false);
				}
				/* else it's a proper RTX with the same src/dst id authenticator/nonce */
			}
		}

		/*
		 *	Now verify the packet passes the attribute filter
		 */
		if (conf->filter_request_vps) {
			if (!fr_pair_validate_relaxed(NULL, conf->filter_request_vps, current->vps)) {
				goto drop_request;
			}
		}

		/*
		 *	Is this a retransmission?
		 */
		if (original) {
			status = RS_RTX;
			original->rt_req++;

			rad_free(&original->packet);

			/* We may of seen the response, but it may of been lost upstream */
			rad_free(&original->linked);

			original->packet = talloc_steal(original, current);

			/* Request may need to be reinserted as the 5 tuple of the response may of changed */
			if (rs_packet_cmp(original, &search) != 0) {
				rbtree_deletebydata(request_tree, original);
			}

			rad_free(&original->expect);
			original->expect = talloc_steal(original, search.expect);

			/* Disarm the timer for the cleanup event for the original request */
			fr_event_delete(event->list, &original->event);
		/*
		 *	...nope it's a new request.
		 */
		} else {
			original = talloc_zero(conf, rs_request_t);
			talloc_set_destructor(original, _request_free);

			original->id = count;
			original->in = event->in;
			original->stats_req = &stats->exchange[current->code];

			/* Set the packet pointer to the start of the buffer*/
			original->capture_p = original->capture;

			original->packet = talloc_steal(original, current);
			original->expect = talloc_steal(original, search.expect);

			if (search.link_vps) {
				bool ret;
				vp_cursor_t cursor;
				VALUE_PAIR *vp;

				for (vp = fr_cursor_init(&cursor, &search.link_vps);
				     vp;
				     vp = fr_cursor_next(&cursor)) {
					fr_pair_steal(original, search.link_vps);
				}
				original->link_vps = search.link_vps;

				/* We should never have conflicts */
				ret = rbtree_insert(link_tree, original);
				RS_ASSERT(ret);
				original->in_link_tree = true;
			}

			/*
			 *	Special case for when were filtering by response,
			 *	we never count any requests as lost, because we
			 *	don't know what the response to that request would
			 *	of been.
			 */
			if (conf->filter_response_vps) {
				original->silent_cleanup = true;
			}
		}

		if (!original->in_request_tree) {
			bool ret;

			/* We should never have conflicts */
			ret = rbtree_insert(request_tree, original);
			RS_ASSERT(ret);
			original->in_request_tree = true;
		}

		/*
		 *	Insert a callback to remove the request from the tree
		 */
		original->packet->timestamp = header->ts;
		rs_tv_add_ms(&header->ts, conf->stats.timeout, &original->when);
		if (!fr_event_insert(event->list, _rs_event, original,
				     &original->when, &original->event)) {
			REDEBUG("Failed inserting new event");

			talloc_free(original);
			return;
		}
		rs_request_to_pcap(event, original, header, data);
		response = false;
		break;
	}

	default:
		REDEBUG("Unsupported code %i", current->code);
		rad_free(&current);

		return;
	}

	rs_tv_sub(&header->ts, &start_pcap, &elapsed);

	/*
	 *	Increase received count
	 */
	stats->exchange[current->code].interval.received_total++;

	/*
	 *	It's a linked response
	 */
	if (original && original->linked) {
		rs_tv_sub(&current->timestamp, &original->packet->timestamp, &latency);

		/*
		 *	Update stats for both the request and response types.
		 *
		 *	This isn't useful for things like Access-Requests, but will be useful for
		 *	CoA and Disconnect Messages, as we get the average latency across both
		 *	response types.
		 *
		 *	It also justifies allocating PW_CODE_MAX instances of rs_latency_t.
		 */
		rs_stats_update_latency(&stats->exchange[current->code], &latency);
		rs_stats_update_latency(&stats->exchange[original->expect->code], &latency);

		/*
		 *	Were filtering on response, now print out the full data from the request
		 */
		if (conf->filter_response && RIDEBUG_ENABLED() && (conf->event_flags & RS_NORMAL)) {
			rs_time_print(timestr, sizeof(timestr), &original->packet->timestamp);
			rs_tv_sub(&original->packet->timestamp, &start_pcap, &elapsed);
			rs_packet_print(original, original->id, RS_NORMAL, original->in,
					original->packet, &elapsed, NULL, false, true);
			rs_tv_sub(&header->ts, &start_pcap, &elapsed);
			rs_time_print(timestr, sizeof(timestr), &header->ts);
		}

		if (conf->event_flags & status) {
			rs_packet_print(original, count, status, event->in, current,
					&elapsed, &latency, response, true);
		}
	/*
	 *	It's the original request
	 *
	 *	If were filtering on responses we can only indicate we received it on response, or timeout.
	 */
	} else if (!conf->filter_response && (conf->event_flags & status)) {
		rs_packet_print(original, original ? original->id : count, status, event->in,
				current, &elapsed, NULL, response, true);
	}

	fflush(fr_log_fp);

	/*
	 *	If it's a unlinked response, we need to free it explicitly, as it will
	 *	not be done by the event queue.
	 */
	if (response && !original) {
		rad_free(&current);
	}

	captured++;
	/*
	 *	We've hit our capture limit, break out of the event loop
	 */
	if ((conf->limit > 0) && (captured >= conf->limit)) {
		INFO("Captured %" PRIu64 " packets, exiting...", captured);
		fr_event_loop_exit(events, 1);
	}
}
