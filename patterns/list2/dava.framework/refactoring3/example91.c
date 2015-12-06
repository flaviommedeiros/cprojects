switch (op)
		{

		case ASN1_PKEY_CTRL_PKCS7_SIGN:
		if (arg1 == 0)
			PKCS7_SIGNER_INFO_get0_algs(arg2, NULL, NULL, &alg);
		break;

		case ASN1_PKEY_CTRL_PKCS7_ENCRYPT:
		if (arg1 == 0)
			PKCS7_RECIP_INFO_get0_alg(arg2, &alg);
		break;
#ifndef OPENSSL_NO_CMS
		case ASN1_PKEY_CTRL_CMS_SIGN:
		if (arg1 == 0)
			CMS_SignerInfo_get0_algs(arg2, NULL, NULL, NULL, &alg);
		break;

		case ASN1_PKEY_CTRL_CMS_ENVELOPE:
		if (arg1 == 0)
			CMS_RecipientInfo_ktri_get0_algs(arg2, NULL, NULL, &alg);
		break;
#endif

		case ASN1_PKEY_CTRL_DEFAULT_MD_NID:
		*(int *)arg2 = NID_sha1;
		return 1;

		default:
		return -2;

		}
