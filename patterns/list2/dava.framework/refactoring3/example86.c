switch (cmd)
		{
#ifndef OPENSSL_NO_RSA
	case SSL_CTRL_SET_TMP_RSA_CB:
		{
		cert->rsa_tmp_cb = (RSA *(*)(SSL *, int, int))fp;
		}
		break;
#endif
#ifndef OPENSSL_NO_DH
	case SSL_CTRL_SET_TMP_DH_CB:
		{
		cert->dh_tmp_cb = (DH *(*)(SSL *, int, int))fp;
		}
		break;
#endif
#ifndef OPENSSL_NO_ECDH
	case SSL_CTRL_SET_TMP_ECDH_CB:
		{
		cert->ecdh_tmp_cb = (EC_KEY *(*)(SSL *, int, int))fp;
		}
		break;
#endif
#ifndef OPENSSL_NO_TLSEXT
	case SSL_CTRL_SET_TLSEXT_SERVERNAME_CB:
		ctx->tlsext_servername_callback=(int (*)(SSL *,int *,void *))fp;
		break;

#ifdef TLSEXT_TYPE_opaque_prf_input
	case SSL_CTRL_SET_TLSEXT_OPAQUE_PRF_INPUT_CB:
		ctx->tlsext_opaque_prf_input_callback = (int (*)(SSL *,void *, size_t, void *))fp;
		break;
#endif

	case SSL_CTRL_SET_TLSEXT_STATUS_REQ_CB:
		ctx->tlsext_status_cb=(int (*)(SSL *,void *))fp;
		break;

	case SSL_CTRL_SET_TLSEXT_TICKET_KEY_CB:
		ctx->tlsext_ticket_key_cb=(int (*)(SSL *,unsigned char  *,
						unsigned char *,
						EVP_CIPHER_CTX *,
						HMAC_CTX *, int))fp;
		break;

#ifndef OPENSSL_NO_SRP
	case SSL_CTRL_SET_SRP_VERIFY_PARAM_CB:
		ctx->srp_ctx.srp_Mask|=SSL_kSRP;
		ctx->srp_ctx.SRP_verify_param_callback=(int (*)(SSL *,void *))fp;
		break;
	case SSL_CTRL_SET_TLS_EXT_SRP_USERNAME_CB:
		ctx->srp_ctx.srp_Mask|=SSL_kSRP;
		ctx->srp_ctx.TLS_ext_srp_username_callback=(int (*)(SSL *,int *,void *))fp;
		break;
	case SSL_CTRL_SET_SRP_GIVE_CLIENT_PWD_CB:
		ctx->srp_ctx.srp_Mask|=SSL_kSRP;
		ctx->srp_ctx.SRP_give_srp_client_pwd_callback=(char *(*)(SSL *,void *))fp;
		break;
#endif
#endif

	default:
		return(0);
		}
