switch (EVP_PKEY_id(ret))
		{
#ifndef OPENSSL_NO_RSA
	case EVP_PKEY_RSA:
		if ((ret->pkey.rsa=d2i_RSAPublicKey(NULL,
			(const unsigned char **)pp,length)) == NULL) /* TMP UGLY CAST */
			{
			ASN1err(ASN1_F_D2I_PUBLICKEY,ERR_R_ASN1_LIB);
			goto err;
			}
		break;
#endif
#ifndef OPENSSL_NO_DSA
	case EVP_PKEY_DSA:
		if (!d2i_DSAPublicKey(&(ret->pkey.dsa),
			(const unsigned char **)pp,length)) /* TMP UGLY CAST */
			{
			ASN1err(ASN1_F_D2I_PUBLICKEY,ERR_R_ASN1_LIB);
			goto err;
			}
		break;
#endif
#ifndef OPENSSL_NO_EC
	case EVP_PKEY_EC:
		if (!o2i_ECPublicKey(&(ret->pkey.ec),
				     (const unsigned char **)pp, length))
			{
			ASN1err(ASN1_F_D2I_PUBLICKEY, ERR_R_ASN1_LIB);
			goto err;
			}
	break;
#endif
	default:
		ASN1err(ASN1_F_D2I_PUBLICKEY,ASN1_R_UNKNOWN_PUBLIC_KEY_TYPE);
		goto err;
		/* break; */
		}
