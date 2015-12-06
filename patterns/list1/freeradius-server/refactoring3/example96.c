switch (vp->da->attr) {
		case PW_CLEARTEXT_PASSWORD:
			auth_func = &pap_auth_clear;
			break;

		case PW_CRYPT_PASSWORD:
			auth_func = &pap_auth_crypt;
			break;

		case PW_MD5_PASSWORD:
			auth_func = &pap_auth_md5;
			break;

		case PW_SMD5_PASSWORD:
			auth_func = &pap_auth_smd5;
			break;

#ifdef HAVE_OPENSSL_EVP_H
		case PW_SHA2_PASSWORD:
			auth_func = &pap_auth_sha2;
			break;

		case PW_SSHA2_224_PASSWORD:
		case PW_SSHA2_256_PASSWORD:
		case PW_SSHA2_384_PASSWORD:
		case PW_SSHA2_512_PASSWORD:
			auth_func = &pap_auth_ssha2;
			break;
#endif

		case PW_SHA_PASSWORD:
			auth_func = &pap_auth_sha;
			break;

		case PW_SSHA_PASSWORD:
			auth_func = &pap_auth_ssha;
			break;

		case PW_NT_PASSWORD:
			auth_func = &pap_auth_nt;
			break;

		case PW_LM_PASSWORD:
			auth_func = &pap_auth_lm;
			break;

		case PW_NS_MTA_MD5_PASSWORD:
			auth_func = &pap_auth_ns_mta_md5;
			break;

		default:
			break;
		}
