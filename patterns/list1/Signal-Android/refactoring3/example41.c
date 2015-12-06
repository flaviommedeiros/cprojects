switch (type)
		{
		case EVP_PKEY_CTRL_RSA_PADDING:
		if ((p1 >= RSA_PKCS1_PADDING) && (p1 <= RSA_PKCS1_PSS_PADDING))
			{
			if (!check_padding_md(rctx->md, p1))
				return 0;
			if (p1 == RSA_PKCS1_PSS_PADDING) 
				{
				if (!(ctx->operation &
				     (EVP_PKEY_OP_SIGN | EVP_PKEY_OP_VERIFY)))
					goto bad_pad;
				if (!rctx->md)
					rctx->md = EVP_sha1();
				}
			if (p1 == RSA_PKCS1_OAEP_PADDING) 
				{
				if (!(ctx->operation & EVP_PKEY_OP_TYPE_CRYPT))
					goto bad_pad;
				if (!rctx->md)
					rctx->md = EVP_sha1();
				}
			rctx->pad_mode = p1;
			return 1;
			}
		bad_pad:
		RSAerr(RSA_F_PKEY_RSA_CTRL,
				RSA_R_ILLEGAL_OR_UNSUPPORTED_PADDING_MODE);
		return -2;

		case EVP_PKEY_CTRL_GET_RSA_PADDING:
		*(int *)p2 = rctx->pad_mode;
		return 1;

		case EVP_PKEY_CTRL_RSA_PSS_SALTLEN:
		case EVP_PKEY_CTRL_GET_RSA_PSS_SALTLEN:
		if (rctx->pad_mode != RSA_PKCS1_PSS_PADDING)
			{
			RSAerr(RSA_F_PKEY_RSA_CTRL, RSA_R_INVALID_PSS_SALTLEN);
			return -2;
			}
		if (type == EVP_PKEY_CTRL_GET_RSA_PSS_SALTLEN)
			*(int *)p2 = rctx->saltlen;
		else
			{
			if (p1 < -2)
				return -2;
			rctx->saltlen = p1;
			}
		return 1;

		case EVP_PKEY_CTRL_RSA_KEYGEN_BITS:
		if (p1 < 256)
			{
			RSAerr(RSA_F_PKEY_RSA_CTRL, RSA_R_INVALID_KEYBITS);
			return -2;
			}
		rctx->nbits = p1;
		return 1;

		case EVP_PKEY_CTRL_RSA_KEYGEN_PUBEXP:
		if (!p2)
			return -2;
		rctx->pub_exp = p2;
		return 1;

		case EVP_PKEY_CTRL_MD:
		if (!check_padding_md(p2, rctx->pad_mode))
			return 0;
		rctx->md = p2;
		return 1;

		case EVP_PKEY_CTRL_RSA_MGF1_MD:
		case EVP_PKEY_CTRL_GET_RSA_MGF1_MD:
		if (rctx->pad_mode != RSA_PKCS1_PSS_PADDING)
			{
			RSAerr(RSA_F_PKEY_RSA_CTRL, RSA_R_INVALID_MGF1_MD);
			return -2;
			}
		if (type == EVP_PKEY_CTRL_GET_RSA_MGF1_MD)
			{
			if (rctx->mgf1md)
				*(const EVP_MD **)p2 = rctx->mgf1md;
			else
				*(const EVP_MD **)p2 = rctx->md;
			}
		else
			rctx->mgf1md = p2;
		return 1;

		case EVP_PKEY_CTRL_DIGESTINIT:
		case EVP_PKEY_CTRL_PKCS7_ENCRYPT:
		case EVP_PKEY_CTRL_PKCS7_DECRYPT:
		case EVP_PKEY_CTRL_PKCS7_SIGN:
		return 1;
#ifndef OPENSSL_NO_CMS
		case EVP_PKEY_CTRL_CMS_DECRYPT:
		{
		X509_ALGOR *alg = NULL;
		ASN1_OBJECT *encalg = NULL;
		if (p2)
			CMS_RecipientInfo_ktri_get0_algs(p2, NULL, NULL, &alg);
		if (alg)
			X509_ALGOR_get0(&encalg, NULL, NULL, alg);
		if (encalg && OBJ_obj2nid(encalg) == NID_rsaesOaep)
			rctx->pad_mode = RSA_PKCS1_OAEP_PADDING;
		}
		case EVP_PKEY_CTRL_CMS_ENCRYPT:
		case EVP_PKEY_CTRL_CMS_SIGN:
		return 1;
#endif
		case EVP_PKEY_CTRL_PEER_KEY:
			RSAerr(RSA_F_PKEY_RSA_CTRL,
			RSA_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
			return -2;	

		default:
		return -2;

		}
