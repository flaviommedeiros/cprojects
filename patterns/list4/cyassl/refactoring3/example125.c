switch (ssl->options.cipherSuite) {

#ifdef HAVE_ECC

#ifdef BUILD_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256
    case TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
    break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
    case TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
    break;
#endif

#ifdef BUILD_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256
    case TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
    break;
#endif

#ifdef BUILD_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256
    case TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
    break;
#endif

#ifdef BUILD_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384
    case TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
    break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384
    case TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
    break;
#endif

#ifdef BUILD_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384
    case TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
    break;
#endif

#ifdef BUILD_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384
    case TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
    break;
#endif

#ifdef BUILD_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA
    case TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA
    case TLS_ECDH_RSA_WITH_AES_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA
    case TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_triple_des;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = DES3_KEY_SIZE;
        ssl->specs.block_size            = DES_BLOCK_SIZE;
        ssl->specs.iv_size               = DES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA
    case TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_triple_des;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = DES3_KEY_SIZE;
        ssl->specs.block_size            = DES_BLOCK_SIZE;
        ssl->specs.iv_size               = DES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_RSA_WITH_RC4_128_SHA
    case TLS_ECDHE_RSA_WITH_RC4_128_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_rc4;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = RC4_KEY_SIZE;
        ssl->specs.iv_size               = 0;
        ssl->specs.block_size            = 0;

        break;
#endif

#ifdef BUILD_TLS_ECDH_RSA_WITH_RC4_128_SHA
    case TLS_ECDH_RSA_WITH_RC4_128_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_rc4;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = RC4_KEY_SIZE;
        ssl->specs.iv_size               = 0;
        ssl->specs.block_size            = 0;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA
    case TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_triple_des;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = DES3_KEY_SIZE;
        ssl->specs.block_size            = DES_BLOCK_SIZE;
        ssl->specs.iv_size               = DES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA
    case TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_triple_des;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = DES3_KEY_SIZE;
        ssl->specs.block_size            = DES_BLOCK_SIZE;
        ssl->specs.iv_size               = DES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_RC4_128_SHA
    case TLS_ECDHE_ECDSA_WITH_RC4_128_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_rc4;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = RC4_KEY_SIZE;
        ssl->specs.iv_size               = 0;
        ssl->specs.block_size            = 0;

        break;
#endif

#ifdef BUILD_TLS_ECDH_ECDSA_WITH_RC4_128_SHA
    case TLS_ECDH_ECDSA_WITH_RC4_128_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_rc4;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = RC4_KEY_SIZE;
        ssl->specs.iv_size               = 0;
        ssl->specs.block_size            = 0;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA
    case TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA
    case TLS_ECDH_RSA_WITH_AES_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
    case TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA
    case TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA
    case TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA
    case TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
    case TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
    case TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
    case TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384
    case TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256
    case TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384
    case TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256
    case TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384
    case TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 1;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8
    case TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_8_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8
    case TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = ecc_diffie_hellman_kea;
        ssl->specs.sig_algo              = ecc_dsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_8_AUTH_SZ;

        break;
#endif
#endif /* HAVE_ECC */

#ifdef BUILD_TLS_RSA_WITH_AES_128_CCM_8
    case TLS_RSA_WITH_AES_128_CCM_8 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_8_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_AES_256_CCM_8
    case TLS_RSA_WITH_AES_256_CCM_8 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_8_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_128_CCM_8
    case TLS_PSK_WITH_AES_128_CCM_8 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_8_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_256_CCM_8
    case TLS_PSK_WITH_AES_256_CCM_8 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_8_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_128_CCM
    case TLS_PSK_WITH_AES_128_CCM :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_16_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_256_CCM
    case TLS_PSK_WITH_AES_256_CCM :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_16_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_DHE_PSK_WITH_AES_128_CCM
    case TLS_DHE_PSK_WITH_AES_128_CCM :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = dhe_psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_16_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_DHE_PSK_WITH_AES_256_CCM
    case TLS_DHE_PSK_WITH_AES_256_CCM :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_ccm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = dhe_psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_CCM_16_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

    default:
        CYASSL_MSG("Unsupported cipher suite, SetCipherSpecs ECC");
        return UNSUPPORTED_SUITE;
    }
