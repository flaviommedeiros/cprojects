if (specifier_id == IANA_SPECIFIER_ID &&
	    (ver == RFC2734_SW_VERSION
#if IS_ENABLED(CONFIG_IPV6)
	     || ver == RFC3146_SW_VERSION
#endif
	    )) {
		buf_ptr += 2;
		length -= IEEE1394_GASP_HDR_SIZE;
		fwnet_incoming_packet(dev, buf_ptr, length, source_node_id,
				      context->card->generation, true);
	}
