if (proto == PROTO_TCP
#ifdef USE_TLS
	    || proto == PROTO_TLS
#endif
	    ) {
		if (parse_headers(msg, HDR_CONTENTLENGTH_F, 0)==-1){
			LM_ERR("error parsing content-length\n");
			goto error;
		}
		if (unlikely(msg->content_length==0)){
			/* not present, we need to add it */
			/* msg->unparsed should point just before the final crlf
			 * - whole message was parsed by the above parse_headers
			 *   which did not find content-length */
			anchor=anchor_lump(msg, msg->unparsed-msg->buf, 0,
												HDR_CONTENTLENGTH_T);
			if (anchor==0){
				LM_ERR("cannot set clen anchor\n");
				goto error;
			}
			body_only=0;
		}else{
			/* compute current content length and compare it with the
			   one in the message */
			body=get_body(msg);
			if (unlikely(body==0)){
				ser_error=E_BAD_REQ;
				LM_ERR("no message body found (missing crlf?)");
				goto error;
			}
			comp_clen=msg->len-(int)(body-msg->buf)+body_delta;
			if (comp_clen!=(int)(long)msg->content_length->parsed){
				/* note: we don't distinguish here between received with
				   wrong content-length and content-length changed, we just
				   fix it automatically in both cases (the reason being
				   that an error message telling we have received a msg-
				   with wrong content-length is of very little use) */
				anchor = del_lump(msg, msg->content_length->body.s-msg->buf,
									msg->content_length->body.len,
									HDR_CONTENTLENGTH_T);
				if (anchor==0) {
					LM_ERR("Can't remove original Content-Length\n");
					goto error;
				}
				body_only=1;
			}
		}
	}else
#endif /* USE_TCP */
	if (body_delta){
		if (parse_headers(msg, HDR_CONTENTLENGTH_F, 0) == -1) {
			LM_ERR("Error parsing Content-Length\n");
			goto error;
		}

		/* The body has been changed, try to find
		 * existing Content-Length
		 */
		/* no need for Content-Length if it's and UDP packet and
		 * it hasn't Content-Length already */
		if (msg->content_length==0){
		    /* content-length doesn't exist, append it */
			/* msg->unparsed should point just before the final crlf
			 * - whole message was parsed by the above parse_headers
			 *   which did not find content-length */
			if (proto!=PROTO_UDP){
				anchor=anchor_lump(msg, msg->unparsed-msg->buf, 0,
													HDR_CONTENTLENGTH_T);
				if (anchor==0){
					LM_ERR("cannot set clen anchor\n");
					goto error;
				}
				body_only=0;
			} /* else
				LM_DBG("UDP packet with no clen => not adding one \n"); */
		}else{
			/* Content-Length has been found, remove it */
			anchor = del_lump(	msg, msg->content_length->body.s - msg->buf,
								msg->content_length->body.len,
								HDR_CONTENTLENGTH_T);
			if (anchor==0) {
				LM_ERR("Can't remove original Content-Length\n");
				goto error;
			}
		}
	}
