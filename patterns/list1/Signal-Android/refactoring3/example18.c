switch (cmd)
		{
	case SSL_CTRL_GET_SESSION_REUSED:
		ret=s->hit;
		break;
	case SSL_CTRL_GET_CLIENT_CERT_REQUEST:
		break;
	case SSL_CTRL_GET_NUM_RENEGOTIATIONS:
		ret=s->s3->num_renegotiations;
		break;
	case SSL_CTRL_CLEAR_NUM_RENEGOTIATIONS:
		ret=s->s3->num_renegotiations;
		s->s3->num_renegotiations=0;
		break;
	case SSL_CTRL_GET_TOTAL_RENEGOTIATIONS:
		ret=s->s3->total_renegotiations;
		break;
	case SSL_CTRL_GET_FLAGS:
		ret=(int)(s->s3->flags);
		break;
#ifndef OPENSSL_NO_RSA
	case SSL_CTRL_NEED_TMP_RSA:
		if ((s->cert != NULL) && (s->cert->rsa_tmp == NULL) &&
		    ((s->cert->pkeys[SSL_PKEY_RSA_ENC].privatekey == NULL) ||
		     (EVP_PKEY_size(s->cert->pkeys[SSL_PKEY_RSA_ENC].privatekey) > (512/8))))
			ret = 1;
		break;
	case SSL_CTRL_SET_TMP_RSA:
		{
			RSA *rsa = (RSA *)parg;
			if (rsa == NULL)
				{
				SSLerr(SSL_F_SSL3_CTRL, ERR_R_PASSED_NULL_PARAMETER);
				return(ret);
				}
			if ((rsa = RSAPrivateKey_dup(rsa)) == NULL)
				{
				SSLerr(SSL_F_SSL3_CTRL, ERR_R_RSA_LIB);
				return(ret);
				}
			if (s->cert->rsa_tmp != NULL)
				RSA_free(s->cert->rsa_tmp);
			s->cert->rsa_tmp = rsa;
			ret = 1;
		}
		break;
	case SSL_CTRL_SET_TMP_RSA_CB:
		{
		SSLerr(SSL_F_SSL3_CTRL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
		return(ret);
		}
		break;
#endif
#ifndef OPENSSL_NO_DH
	case SSL_CTRL_SET_TMP_DH:
		{
			DH *dh = (DH *)parg;
			if (dh == NULL)
				{
				SSLerr(SSL_F_SSL3_CTRL, ERR_R_PASSED_NULL_PARAMETER);
				return(ret);
				}
			if ((dh = DHparams_dup(dh)) == NULL)
				{
				SSLerr(SSL_F_SSL3_CTRL, ERR_R_DH_LIB);
				return(ret);
				}
			if (!(s->options & SSL_OP_SINGLE_DH_USE))
				{
				if (!DH_generate_key(dh))
					{
					DH_free(dh);
					SSLerr(SSL_F_SSL3_CTRL, ERR_R_DH_LIB);
					return(ret);
					}
				}
			if (s->cert->dh_tmp != NULL)
				DH_free(s->cert->dh_tmp);
			s->cert->dh_tmp = dh;
			ret = 1;
		}
		break;
	case SSL_CTRL_SET_TMP_DH_CB:
		{
		SSLerr(SSL_F_SSL3_CTRL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
		return(ret);
		}
		break;
#endif
#ifndef OPENSSL_NO_ECDH
	case SSL_CTRL_SET_TMP_ECDH:
		{
		EC_KEY *ecdh = NULL;
 			
		if (parg == NULL)
			{
			SSLerr(SSL_F_SSL3_CTRL, ERR_R_PASSED_NULL_PARAMETER);
			return(ret);
			}
		if (!EC_KEY_up_ref((EC_KEY *)parg))
			{
			SSLerr(SSL_F_SSL3_CTRL,ERR_R_ECDH_LIB);
			return(ret);
			}
		ecdh = (EC_KEY *)parg;
		if (!(s->options & SSL_OP_SINGLE_ECDH_USE))
			{
			if (!EC_KEY_generate_key(ecdh))
				{
				EC_KEY_free(ecdh);
				SSLerr(SSL_F_SSL3_CTRL,ERR_R_ECDH_LIB);
				return(ret);
				}
			}
		if (s->cert->ecdh_tmp != NULL)
			EC_KEY_free(s->cert->ecdh_tmp);
		s->cert->ecdh_tmp = ecdh;
		ret = 1;
		}
		break;
	case SSL_CTRL_SET_TMP_ECDH_CB:
		{
		SSLerr(SSL_F_SSL3_CTRL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
		return(ret);
		}
		break;
#endif /* !OPENSSL_NO_ECDH */
#ifndef OPENSSL_NO_TLSEXT
	case SSL_CTRL_SET_TLSEXT_HOSTNAME:
 		if (larg == TLSEXT_NAMETYPE_host_name)
			{
			if (s->tlsext_hostname != NULL) 
				OPENSSL_free(s->tlsext_hostname);
			s->tlsext_hostname = NULL;

			ret = 1;
			if (parg == NULL) 
				break;
			if (strlen((char *)parg) > TLSEXT_MAXLEN_host_name)
				{
				SSLerr(SSL_F_SSL3_CTRL, SSL_R_SSL3_EXT_INVALID_SERVERNAME);
				return 0;
				}
			if ((s->tlsext_hostname = BUF_strdup((char *)parg)) == NULL)
				{
				SSLerr(SSL_F_SSL3_CTRL, ERR_R_INTERNAL_ERROR);
				return 0;
				}
			}
		else
			{
			SSLerr(SSL_F_SSL3_CTRL, SSL_R_SSL3_EXT_INVALID_SERVERNAME_TYPE);
			return 0;
			}
 		break;
	case SSL_CTRL_SET_TLSEXT_DEBUG_ARG:
		s->tlsext_debug_arg=parg;
		ret = 1;
		break;

#ifdef TLSEXT_TYPE_opaque_prf_input
	case SSL_CTRL_SET_TLSEXT_OPAQUE_PRF_INPUT:
		if (larg > 12288) /* actual internal limit is 2^16 for the complete hello message
		                   * (including the cert chain and everything) */
			{
			SSLerr(SSL_F_SSL3_CTRL, SSL_R_OPAQUE_PRF_INPUT_TOO_LONG);
			break;
			}
		if (s->tlsext_opaque_prf_input != NULL)
			OPENSSL_free(s->tlsext_opaque_prf_input);
		if ((size_t)larg == 0)
			s->tlsext_opaque_prf_input = OPENSSL_malloc(1); /* dummy byte just to get non-NULL */
		else
			s->tlsext_opaque_prf_input = BUF_memdup(parg, (size_t)larg);
		if (s->tlsext_opaque_prf_input != NULL)
			{
			s->tlsext_opaque_prf_input_len = (size_t)larg;
			ret = 1;
			}
		else
			s->tlsext_opaque_prf_input_len = 0;
		break;
#endif

	case SSL_CTRL_SET_TLSEXT_STATUS_REQ_TYPE:
		s->tlsext_status_type=larg;
		ret = 1;
		break;

	case SSL_CTRL_GET_TLSEXT_STATUS_REQ_EXTS:
		*(STACK_OF(X509_EXTENSION) **)parg = s->tlsext_ocsp_exts;
		ret = 1;
		break;

	case SSL_CTRL_SET_TLSEXT_STATUS_REQ_EXTS:
		s->tlsext_ocsp_exts = parg;
		ret = 1;
		break;

	case SSL_CTRL_GET_TLSEXT_STATUS_REQ_IDS:
		*(STACK_OF(OCSP_RESPID) **)parg = s->tlsext_ocsp_ids;
		ret = 1;
		break;

	case SSL_CTRL_SET_TLSEXT_STATUS_REQ_IDS:
		s->tlsext_ocsp_ids = parg;
		ret = 1;
		break;

	case SSL_CTRL_GET_TLSEXT_STATUS_REQ_OCSP_RESP:
		*(unsigned char **)parg = s->tlsext_ocsp_resp;
		return s->tlsext_ocsp_resplen;
		
	case SSL_CTRL_SET_TLSEXT_STATUS_REQ_OCSP_RESP:
		if (s->tlsext_ocsp_resp)
			OPENSSL_free(s->tlsext_ocsp_resp);
		s->tlsext_ocsp_resp = parg;
		s->tlsext_ocsp_resplen = larg;
		ret = 1;
		break;

#ifndef OPENSSL_NO_HEARTBEATS
	case SSL_CTRL_TLS_EXT_SEND_HEARTBEAT:
		if (SSL_version(s) == DTLS1_VERSION || SSL_version(s) == DTLS1_BAD_VER)
			ret = dtls1_heartbeat(s);
		else
			ret = tls1_heartbeat(s);
		break;

	case SSL_CTRL_GET_TLS_EXT_HEARTBEAT_PENDING:
		ret = s->tlsext_hb_pending;
		break;

	case SSL_CTRL_SET_TLS_EXT_HEARTBEAT_NO_REQUESTS:
		if (larg)
			s->tlsext_heartbeat |= SSL_TLSEXT_HB_DONT_RECV_REQUESTS;
		else
			s->tlsext_heartbeat &= ~SSL_TLSEXT_HB_DONT_RECV_REQUESTS;
		ret = 1;
		break;
#endif
	case SSL_CTRL_CHANNEL_ID:
		s->tlsext_channel_id_enabled = 1;
		ret = 1;
		break;

	case SSL_CTRL_SET_CHANNEL_ID:
		if (s->server)
			break;
		s->tlsext_channel_id_enabled = 1;
		if (EVP_PKEY_bits(parg) != 256)
			{
			SSLerr(SSL_F_SSL3_CTRL,SSL_R_CHANNEL_ID_NOT_P256);
			break;
			}
		if (s->tlsext_channel_id_private)
			EVP_PKEY_free(s->tlsext_channel_id_private);
		s->tlsext_channel_id_private = EVP_PKEY_dup((EVP_PKEY*) parg);
		ret = 1;
		break;

	case SSL_CTRL_GET_CHANNEL_ID:
		if (!s->server)
			break;
		if (!s->s3->tlsext_channel_id_valid)
			break;
		memcpy(parg, s->s3->tlsext_channel_id, larg < 64 ? larg : 64);
		return 64;

#endif /* !OPENSSL_NO_TLSEXT */
	default:
		break;
		}
