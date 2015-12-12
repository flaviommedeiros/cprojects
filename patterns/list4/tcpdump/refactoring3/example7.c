switch (phase) {
#ifndef USE_IPSECDOI_IN_PHASE1
	case 1:
#endif
	default:
		ND_PRINT((ndo," idtype=%s", STR_OR_ID(id.d.id_type, idtypestr)));
		ND_PRINT((ndo," doi_data=%u",
			  (uint32_t)(ntohl(id.d.doi_data) & 0xffffff)));
		break;

#ifdef USE_IPSECDOI_IN_PHASE1
	case 1:
#endif
	case 2:
	    {
		const struct ipsecdoi_id *doi_p;
		struct ipsecdoi_id doi_id;
		struct protoent *pe;

		doi_p = (const struct ipsecdoi_id *)ext;
		ND_TCHECK(*doi_p);
		UNALIGNED_MEMCPY(&doi_id, ext, sizeof(doi_id));
		ND_PRINT((ndo," idtype=%s", STR_OR_ID(doi_id.type, ipsecidtypestr)));
		/* A protocol ID of 0 DOES NOT mean IPPROTO_IP! */
		pe = doi_id.proto_id ? getprotobynumber(doi_id.proto_id) : NULL;
		if (pe)
			ND_PRINT((ndo," protoid=%s", pe->p_name));
		else
			ND_PRINT((ndo," protoid=%u", doi_id.proto_id));
		ND_PRINT((ndo," port=%d", ntohs(doi_id.port)));
		if (!len)
			break;
		if (data == NULL)
			goto trunc;
		ND_TCHECK2(*data, len);
		switch (doi_id.type) {
		case IPSECDOI_ID_IPV4_ADDR:
			if (len < 4)
				ND_PRINT((ndo," len=%d [bad: < 4]", len));
			else
				ND_PRINT((ndo," len=%d %s", len, ipaddr_string(ndo, data)));
			len = 0;
			break;
		case IPSECDOI_ID_FQDN:
		case IPSECDOI_ID_USER_FQDN:
		    {
			int i;
			ND_PRINT((ndo," len=%d ", len));
			for (i = 0; i < len; i++)
				safeputchar(ndo, data[i]);
			len = 0;
			break;
		    }
		case IPSECDOI_ID_IPV4_ADDR_SUBNET:
		    {
			const u_char *mask;
			if (len < 8)
				ND_PRINT((ndo," len=%d [bad: < 8]", len));
			else {
				mask = data + sizeof(struct in_addr);
				ND_PRINT((ndo," len=%d %s/%u.%u.%u.%u", len,
					  ipaddr_string(ndo, data),
					  mask[0], mask[1], mask[2], mask[3]));
			}
			len = 0;
			break;
		    }
		case IPSECDOI_ID_IPV6_ADDR:
			if (len < 16)
				ND_PRINT((ndo," len=%d [bad: < 16]", len));
			else
				ND_PRINT((ndo," len=%d %s", len, ip6addr_string(ndo, data)));
			len = 0;
			break;
		case IPSECDOI_ID_IPV6_ADDR_SUBNET:
		    {
			const u_char *mask;
			if (len < 20)
				ND_PRINT((ndo," len=%d [bad: < 20]", len));
			else {
				mask = (const u_char *)(data + sizeof(struct in6_addr));
				/*XXX*/
				ND_PRINT((ndo," len=%d %s/0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", len,
					  ip6addr_string(ndo, data),
					  mask[0], mask[1], mask[2], mask[3],
					  mask[4], mask[5], mask[6], mask[7],
					  mask[8], mask[9], mask[10], mask[11],
					  mask[12], mask[13], mask[14], mask[15]));
			}
			len = 0;
			break;
		    }
		case IPSECDOI_ID_IPV4_ADDR_RANGE:
			if (len < 8)
				ND_PRINT((ndo," len=%d [bad: < 8]", len));
			else {
				ND_PRINT((ndo," len=%d %s-%s", len,
					  ipaddr_string(ndo, data),
					  ipaddr_string(ndo, data + sizeof(struct in_addr))));
			}
			len = 0;
			break;
		case IPSECDOI_ID_IPV6_ADDR_RANGE:
			if (len < 32)
				ND_PRINT((ndo," len=%d [bad: < 32]", len));
			else {
				ND_PRINT((ndo," len=%d %s-%s", len,
					  ip6addr_string(ndo, data),
					  ip6addr_string(ndo, data + sizeof(struct in6_addr))));
			}
			len = 0;
			break;
		case IPSECDOI_ID_DER_ASN1_DN:
		case IPSECDOI_ID_DER_ASN1_GN:
		case IPSECDOI_ID_KEY_ID:
			break;
		}
		break;
	    }
	}
