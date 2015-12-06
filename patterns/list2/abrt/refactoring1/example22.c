if ((*key)->ops && der_heim_oid_cmp((*key)->ops->key_oid, ASN1_OID_ID_PKCS1_RSAENCRYPTION) == 0) {
	if ((*key)->private_key.rsa)
	    RSA_free((*key)->private_key.rsa);
#ifdef HAVE_OPENSSL
    } else if ((*key)->ops && der_heim_oid_cmp((*key)->ops->key_oid, ASN1_OID_ID_ECPUBLICKEY) == 0) {
	if ((*key)->private_key.ecdsa)
	    EC_KEY_free((*key)->private_key.ecdsa);
#endif
    }
#endif
