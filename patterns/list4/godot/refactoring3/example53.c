switch (op)
		{
		case ASN1_PKEY_CTRL_PKCS7_SIGN:
		if (arg1 == 0)
			{
			int snid, hnid;
			X509_ALGOR *alg1, *alg2;
			PKCS7_SIGNER_INFO_get0_algs(arg2, NULL, &alg1, &alg2);
			if (alg1 == NULL || alg1->algorithm == NULL)
				return -1;
			hnid = OBJ_obj2nid(alg1->algorithm);
			if (hnid == NID_undef)
				return -1;
			if (!OBJ_find_sigid_by_algs(&snid, hnid, EVP_PKEY_id(pkey)))
				return -1; 
			X509_ALGOR_set0(alg2, OBJ_nid2obj(snid), V_ASN1_UNDEF, 0);
			}
		return 1;
#ifndef OPENSSL_NO_CMS
		case ASN1_PKEY_CTRL_CMS_SIGN:
		if (arg1 == 0)
			{
			int snid, hnid;
			X509_ALGOR *alg1, *alg2;
			CMS_SignerInfo_get0_algs(arg2, NULL, NULL,
								&alg1, &alg2);
			if (alg1 == NULL || alg1->algorithm == NULL)
				return -1;
			hnid = OBJ_obj2nid(alg1->algorithm);
			if (hnid == NID_undef)
				return -1;
			if (!OBJ_find_sigid_by_algs(&snid, hnid, EVP_PKEY_id(pkey)))
				return -1; 
			X509_ALGOR_set0(alg2, OBJ_nid2obj(snid), V_ASN1_UNDEF, 0);
			}
		return 1;
#endif

		case ASN1_PKEY_CTRL_DEFAULT_MD_NID:
		*(int *)arg2 = NID_sha1;
		return 2;

		default:
		return -2;

		}
