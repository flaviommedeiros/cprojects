switch (type)
		{
		case EVP_PKEY_CTRL_MD:
		{
		if (EVP_MD_type((const EVP_MD *)p2) != NID_id_GostR3411_94)
			{
			GOSTerr(GOST_F_PKEY_GOST_CTRL, GOST_R_INVALID_DIGEST_TYPE);
			return 0;
			}
		pctx->md = (EVP_MD *)p2;
		return 1;
		}
		break;

		case EVP_PKEY_CTRL_PKCS7_ENCRYPT:
		case EVP_PKEY_CTRL_PKCS7_DECRYPT:
		case EVP_PKEY_CTRL_PKCS7_SIGN:
		case EVP_PKEY_CTRL_DIGESTINIT:
#ifndef OPENSSL_NO_CMS		
		case EVP_PKEY_CTRL_CMS_ENCRYPT:
		case EVP_PKEY_CTRL_CMS_DECRYPT:
		case EVP_PKEY_CTRL_CMS_SIGN:
#endif		
			return 1;

		case EVP_PKEY_CTRL_GOST_PARAMSET:
			pctx->sign_param_nid = (int)p1;
			return 1;
		case EVP_PKEY_CTRL_SET_IV:
			pctx->shared_ukm=OPENSSL_malloc((int)p1);
			memcpy(pctx->shared_ukm,p2,(int) p1);
			return 1;
		case EVP_PKEY_CTRL_PEER_KEY:
			if (p1 == 0 || p1 == 1) /* call from EVP_PKEY_derive_set_peer */
				return 1;
			if (p1 == 2)		/* TLS: peer key used? */
				return pctx->peer_key_used;
			if (p1 == 3)		/* TLS: peer key used! */
				return (pctx->peer_key_used = 1);
			return -2;
		}
