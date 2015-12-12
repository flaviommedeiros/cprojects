switch(hash_alg)
		{
#ifndef OPENSSL_NO_SHA
		case TLSEXT_hash_sha1:
		return EVP_sha1();
#endif
#ifndef OPENSSL_NO_SHA256
		case TLSEXT_hash_sha224:
		return EVP_sha224();

		case TLSEXT_hash_sha256:
		return EVP_sha256();
#endif
#ifndef OPENSSL_NO_SHA512
		case TLSEXT_hash_sha384:
		return EVP_sha384();

		case TLSEXT_hash_sha512:
		return EVP_sha512();
#endif
		default:
		return NULL;

		}
