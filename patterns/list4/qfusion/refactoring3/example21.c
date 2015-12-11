switch (op) {
    case ASN1_PKEY_CTRL_PKCS7_SIGN:
        if (arg1 == 0) {
            X509_ALGOR *alg1 = NULL, *alg2 = NULL;
            int nid = EVP_PKEY_base_id(pkey);
            PKCS7_SIGNER_INFO_get0_algs((PKCS7_SIGNER_INFO *)arg2,
                                        NULL, &alg1, &alg2);
            X509_ALGOR_set0(alg1, OBJ_nid2obj(NID_id_GostR3411_94),
                            V_ASN1_NULL, 0);
            if (nid == NID_undef) {
                return (-1);
            }
            X509_ALGOR_set0(alg2, OBJ_nid2obj(nid), V_ASN1_NULL, 0);
        }
        return 1;
#ifndef OPENSSL_NO_CMS
    case ASN1_PKEY_CTRL_CMS_SIGN:
        if (arg1 == 0) {
            X509_ALGOR *alg1 = NULL, *alg2 = NULL;
            int nid = EVP_PKEY_base_id(pkey);
            CMS_SignerInfo_get0_algs((CMS_SignerInfo *)arg2,
                                     NULL, NULL, &alg1, &alg2);
            X509_ALGOR_set0(alg1, OBJ_nid2obj(NID_id_GostR3411_94),
                            V_ASN1_NULL, 0);
            if (nid == NID_undef) {
                return (-1);
            }
            X509_ALGOR_set0(alg2, OBJ_nid2obj(nid), V_ASN1_NULL, 0);
        }
        return 1;
#endif
    case ASN1_PKEY_CTRL_PKCS7_ENCRYPT:
        if (arg1 == 0) {
            X509_ALGOR *alg;
            ASN1_STRING *params = encode_gost_algor_params(pkey);
            if (!params) {
                return -1;
            }
            PKCS7_RECIP_INFO_get0_alg((PKCS7_RECIP_INFO *)arg2, &alg);
            X509_ALGOR_set0(alg, OBJ_nid2obj(pkey->type),
                            V_ASN1_SEQUENCE, params);
        }
        return 1;
#ifndef OPENSSL_NO_CMS
    case ASN1_PKEY_CTRL_CMS_ENVELOPE:
        if (arg1 == 0) {
            X509_ALGOR *alg = NULL;
            ASN1_STRING *params = encode_gost_algor_params(pkey);
            if (!params) {
                return -1;
            }
            CMS_RecipientInfo_ktri_get0_algs((CMS_RecipientInfo *)arg2, NULL,
                                             NULL, &alg);
            X509_ALGOR_set0(alg, OBJ_nid2obj(pkey->type), V_ASN1_SEQUENCE,
                            params);
        }
        return 1;
#endif
    case ASN1_PKEY_CTRL_DEFAULT_MD_NID:
        *(int *)arg2 = NID_id_GostR3411_94;
        return 2;
    }
