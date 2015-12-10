switch (wsi->state) {
#ifdef LWS_USE_HTTP2
	case WSI_STATE_HTTP2_AWAIT_CLIENT_PREFACE:
	case WSI_STATE_HTTP2_ESTABLISHED_PRE_SETTINGS:
	case WSI_STATE_HTTP2_ESTABLISHED:
		n = 0;
		while (n < len) {
			/*
			 * we were accepting input but now we stopped doing so
			 */
			if (!(wsi->rxflow_change_to & LWS_RXFLOW_ALLOW)) {
				lws_rxflow_cache(wsi, buf, n, len);

				return 1;
			}

			/* account for what we're using in rxflow buffer */
			if (wsi->rxflow_buffer)
				wsi->rxflow_pos++;
			if (lws_http2_parser(context, wsi, buf[n++]))
				goto bail;
		}
		break;
#endif
http_new:
	case WSI_STATE_HTTP:
		wsi->hdr_parsing_completed = 0;
		/* fallthru */
	case WSI_STATE_HTTP_ISSUING_FILE:
		wsi->state = WSI_STATE_HTTP_HEADERS;
		wsi->u.hdr.parser_state = WSI_TOKEN_NAME_PART;
		wsi->u.hdr.lextable_pos = 0;
		/* fallthru */
	case WSI_STATE_HTTP_HEADERS:
		lwsl_parser("issuing %d bytes to parser\n", (int)len);

		if (lws_handshake_client(wsi, &buf, len))
			goto bail;

		last_char = buf;
		if (lws_handshake_server(context, wsi, &buf, len))
			/* Handshake indicates this session is done. */
			goto bail;

		/* It's possible that we've exhausted our data already, but
		 * lws_handshake_server doesn't update len for us. Figure out how
		 * much was read, so that we can proceed appropriately: */
		len -= (buf - last_char);

		if (!wsi->hdr_parsing_completed)
			/* More header content on the way */
			goto read_ok;

		switch (wsi->state) {
			case WSI_STATE_HTTP:
			case WSI_STATE_HTTP_HEADERS:
				goto http_complete;
			case WSI_STATE_HTTP_ISSUING_FILE:
				goto read_ok;
			case WSI_STATE_HTTP_BODY:
				wsi->u.http.content_remain =
						wsi->u.http.content_length;
				if (wsi->u.http.content_remain)
					goto http_postbody;

				/* there is no POST content */
				goto postbody_completion;
			default:
				break;
		}
		break;

	case WSI_STATE_HTTP_BODY:
http_postbody:
		while (len && wsi->u.http.content_remain) {
			/* Copy as much as possible, up to the limit of:
			 * what we have in the read buffer (len)
			 * remaining portion of the POST body (content_remain)
			 */
			body_chunk_len = min(wsi->u.http.content_remain,len);
			wsi->u.http.content_remain -= body_chunk_len;
			len -= body_chunk_len;

			n = wsi->protocol->callback(
				wsi->protocol->owning_server, wsi,
				LWS_CALLBACK_HTTP_BODY, wsi->user_space,
				buf, body_chunk_len);
			if (n)
				goto bail;

			buf += body_chunk_len;

			if (wsi->u.http.content_remain)  {
				lws_set_timeout(wsi, PENDING_TIMEOUT_HTTP_CONTENT,
						AWAITING_TIMEOUT);
				break;
			}
			/* he sent all the content in time */
postbody_completion:
			lws_set_timeout(wsi, NO_PENDING_TIMEOUT, 0);
			n = wsi->protocol->callback(
				wsi->protocol->owning_server, wsi,
				LWS_CALLBACK_HTTP_BODY_COMPLETION,
				wsi->user_space, NULL, 0);
			if (n)
				goto bail;

			goto http_complete;
		}
		break;

	case WSI_STATE_ESTABLISHED:
	case WSI_STATE_AWAITING_CLOSE_ACK:
		if (lws_handshake_client(wsi, &buf, len))
			goto bail;
		switch (wsi->mode) {
		case LWS_CONNMODE_WS_SERVING:

			if (lws_interpret_incoming_packet(wsi, buf, len) < 0) {
				lwsl_info("interpret_incoming_packet has bailed\n");
				goto bail;
			}
			break;
		}
		break;
	default:
		lwsl_err("lws_read: Unhandled state\n");
		break;
	}
