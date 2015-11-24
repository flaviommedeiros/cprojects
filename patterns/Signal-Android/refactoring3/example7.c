switch(sig_alg)
			{
#ifndef OPENSSL_NO_RSA
			case TLSEXT_signature_rsa:
			digest_ptr = &s->s3->digest_rsa;
			break;
#endif
#ifndef OPENSSL_NO_DSA
			case TLSEXT_signature_dsa:
			digest_ptr = &s->s3->digest_dsa;
			break;
#endif
#ifndef OPENSSL_NO_ECDSA
			case TLSEXT_signature_ecdsa:
			digest_ptr = &s->s3->digest_ecdsa;
			break;
#endif
			default:
			continue;
			}
