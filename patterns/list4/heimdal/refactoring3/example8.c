switch (rr->type) {
    case rk_ns_t_ns:
    case rk_ns_t_cname:
    case rk_ns_t_ptr:
	rr->u.txt = strdup(pRec->Data.NS.pNameHost);
	if(rr->u.txt == NULL) {
	    dns_free_rr(rr);
	    return NULL;
	}
	break;

    case rk_ns_t_mx:
    case rk_ns_t_afsdb:{
	size_t hostlen = strnlen(pRec->Data.MX.pNameExchange, DNS_MAX_NAME_LENGTH);

	rr->u.mx = (struct mx_record *)malloc(sizeof(struct mx_record) +
					      hostlen);
	if (rr->u.mx == NULL) {
	    dns_free_rr(rr);
	    return NULL;
	}

	strcpy_s(rr->u.mx->domain, hostlen + 1, pRec->Data.MX.pNameExchange);
	rr->u.mx->preference = pRec->Data.MX.wPreference;
	break;
    }

    case rk_ns_t_srv:{
	size_t hostlen = strnlen(pRec->Data.SRV.pNameTarget, DNS_MAX_NAME_LENGTH);

	rr->u.srv =
	    (struct srv_record*)malloc(sizeof(struct srv_record) +
				       hostlen);
	if(rr->u.srv == NULL) {
	    dns_free_rr(rr);
	    return NULL;
	}

	rr->u.srv->priority = pRec->Data.SRV.wPriority;
	rr->u.srv->weight = pRec->Data.SRV.wWeight;
	rr->u.srv->port = pRec->Data.SRV.wPort;
	strcpy_s(rr->u.srv->target, hostlen + 1, pRec->Data.SRV.pNameTarget);

	break;
    }

    case rk_ns_t_txt:{
	size_t len;

	if (pRec->Data.TXT.dwStringCount == 0) {
	    rr->u.txt = strdup("");
	    break;
	}

	len = strnlen(pRec->Data.TXT.pStringArray[0], DNS_MAX_TEXT_STRING_LENGTH);

	rr->u.txt = (char *)malloc(len + 1);
	strcpy_s(rr->u.txt, len + 1, pRec->Data.TXT.pStringArray[0]);

	break;
    }

    case rk_ns_t_key : {
	size_t key_len;

	if (pRec->wDataLength < 4) {
	    dns_free_rr(rr);
	    return NULL;
	}

	key_len = pRec->wDataLength - 4;
	rr->u.key = malloc (sizeof(*rr->u.key) + key_len - 1);
	if (rr->u.key == NULL) {
	    dns_free_rr(rr);
	    return NULL;
	}

	rr->u.key->flags     = pRec->Data.KEY.wFlags;
	rr->u.key->protocol  = pRec->Data.KEY.chProtocol;
	rr->u.key->algorithm = pRec->Data.KEY.chAlgorithm;
	rr->u.key->key_len   = key_len;
	memcpy_s (rr->u.key->key_data, key_len,
		  pRec->Data.KEY.Key, key_len);
	break;
    }

    case rk_ns_t_sig : {
	size_t sig_len, hostlen;

	if(pRec->wDataLength <= 18) {
	    dns_free_rr(rr);
	    return NULL;
	}

	sig_len = pRec->wDataLength;

	hostlen = strnlen(pRec->Data.SIG.pNameSigner, DNS_MAX_NAME_LENGTH);

	rr->u.sig = malloc(sizeof(*rr->u.sig)
			      + hostlen + sig_len);
	if (rr->u.sig == NULL) {
	    dns_free_rr(rr);
	    return NULL;
	}
	rr->u.sig->type           = pRec->Data.SIG.wTypeCovered;
	rr->u.sig->algorithm      = pRec->Data.SIG.chAlgorithm;
	rr->u.sig->labels         = pRec->Data.SIG.chLabelCount;
	rr->u.sig->orig_ttl       = pRec->Data.SIG.dwOriginalTtl;
	rr->u.sig->sig_expiration = pRec->Data.SIG.dwExpiration;
	rr->u.sig->sig_inception  = pRec->Data.SIG.dwTimeSigned;
	rr->u.sig->key_tag        = pRec->Data.SIG.wKeyTag;
	rr->u.sig->sig_len        = sig_len;
	memcpy_s (rr->u.sig->sig_data, sig_len,
		  pRec->Data.SIG.Signature, sig_len);
	rr->u.sig->signer         = &rr->u.sig->sig_data[sig_len];
	strcpy_s(rr->u.sig->signer, hostlen + 1, pRec->Data.SIG.pNameSigner);
	break;
    }

#ifdef DNS_TYPE_DS
    case rk_ns_t_ds: {
	rr->u.ds = malloc (sizeof(*rr->u.ds) + pRec->Data.DS.wDigestLength - 1);
	if (rr->u.ds == NULL) {
	    dns_free_rr(rr);
	    return NULL;
	}

	rr->u.ds->key_tag     = pRec->Data.DS.wKeyTag;
	rr->u.ds->algorithm   = pRec->Data.DS.chAlgorithm;
	rr->u.ds->digest_type = pRec->Data.DS.chDigestType;
	rr->u.ds->digest_len  = pRec->Data.DS.wDigestLength;
	memcpy_s (rr->u.ds->digest_data, pRec->Data.DS.wDigestLength,
		  pRec->Data.DS.Digest, pRec->Data.DS.wDigestLength);
	break;
    }
#endif

    default:
	dns_free_rr(rr);
	return NULL;
    }
