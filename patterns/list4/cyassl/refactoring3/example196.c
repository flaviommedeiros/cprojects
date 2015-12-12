switch (ssl->options.cipherSuite) {

#ifdef BUILD_SSL_RSA_WITH_RC4_128_SHA
    case SSL_RSA_WITH_RC4_128_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_rc4;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = RC4_KEY_SIZE;
        ssl->specs.iv_size               = 0;
        ssl->specs.block_size            = 0;

        break;
#endif

#ifdef BUILD_TLS_NTRU_RSA_WITH_RC4_128_SHA
    case TLS_NTRU_RSA_WITH_RC4_128_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_rc4;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ntru_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = RC4_KEY_SIZE;
        ssl->specs.iv_size               = 0;
        ssl->specs.block_size            = 0;

        break;
#endif

#ifdef BUILD_SSL_RSA_WITH_RC4_128_MD5
    case SSL_RSA_WITH_RC4_128_MD5 :
        ssl->specs.bulk_cipher_algorithm = cyassl_rc4;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = md5_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = MD5_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_MD5;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = RC4_KEY_SIZE;
        ssl->specs.iv_size               = 0;
        ssl->specs.block_size            = 0;

        break;
#endif

#ifdef BUILD_SSL_RSA_WITH_3DES_EDE_CBC_SHA
    case SSL_RSA_WITH_3DES_EDE_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_triple_des;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = DES3_KEY_SIZE;
        ssl->specs.block_size            = DES_BLOCK_SIZE;
        ssl->specs.iv_size               = DES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_NTRU_RSA_WITH_3DES_EDE_CBC_SHA
    case TLS_NTRU_RSA_WITH_3DES_EDE_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_triple_des;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ntru_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = DES3_KEY_SIZE;
        ssl->specs.block_size            = DES_BLOCK_SIZE;
        ssl->specs.iv_size               = DES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_AES_128_CBC_SHA
    case TLS_RSA_WITH_AES_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_AES_128_CBC_SHA256
    case TLS_RSA_WITH_AES_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_NULL_SHA
    case TLS_RSA_WITH_NULL_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_cipher_null;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = 0;
        ssl->specs.block_size            = 0;
        ssl->specs.iv_size               = 0;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_NULL_SHA256
    case TLS_RSA_WITH_NULL_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_cipher_null;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = 0;
        ssl->specs.block_size            = 0;
        ssl->specs.iv_size               = 0;

        break;
#endif

#ifdef BUILD_TLS_NTRU_RSA_WITH_AES_128_CBC_SHA
    case TLS_NTRU_RSA_WITH_AES_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ntru_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_AES_256_CBC_SHA
    case TLS_RSA_WITH_AES_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_AES_256_CBC_SHA256
    case TLS_RSA_WITH_AES_256_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_NTRU_RSA_WITH_AES_256_CBC_SHA
    case TLS_NTRU_RSA_WITH_AES_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = ntru_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_128_GCM_SHA256
    case TLS_PSK_WITH_AES_128_GCM_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
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
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_256_GCM_SHA384
    case TLS_PSK_WITH_AES_256_GCM_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_DHE_PSK_WITH_AES_128_GCM_SHA256
    case TLS_DHE_PSK_WITH_AES_128_GCM_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
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
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_DHE_PSK_WITH_AES_256_GCM_SHA384
    case TLS_DHE_PSK_WITH_AES_256_GCM_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = dhe_psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AEAD_IMP_IV_SZ;
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_128_CBC_SHA256
    case TLS_PSK_WITH_AES_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_256_CBC_SHA384
    case TLS_PSK_WITH_AES_256_CBC_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_DHE_PSK_WITH_AES_128_CBC_SHA256
    case TLS_DHE_PSK_WITH_AES_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = dhe_psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_DHE_PSK_WITH_AES_256_CBC_SHA384
    case TLS_DHE_PSK_WITH_AES_256_CBC_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = dhe_psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_128_CBC_SHA
    case TLS_PSK_WITH_AES_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_AES_256_CBC_SHA
    case TLS_PSK_WITH_AES_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_NULL_SHA256
    case TLS_PSK_WITH_NULL_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_cipher_null;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = 0;
        ssl->specs.block_size            = 0;
        ssl->specs.iv_size               = 0;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_NULL_SHA384
    case TLS_PSK_WITH_NULL_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_cipher_null;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = 0;
        ssl->specs.block_size            = 0;
        ssl->specs.iv_size               = 0;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_PSK_WITH_NULL_SHA
    case TLS_PSK_WITH_NULL_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_cipher_null;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = 0;
        ssl->specs.block_size            = 0;
        ssl->specs.iv_size               = 0;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_DHE_PSK_WITH_NULL_SHA256
    case TLS_DHE_PSK_WITH_NULL_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_cipher_null;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = dhe_psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = 0;
        ssl->specs.block_size            = 0;
        ssl->specs.iv_size               = 0;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_DHE_PSK_WITH_NULL_SHA384
    case TLS_DHE_PSK_WITH_NULL_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_cipher_null;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = dhe_psk_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA384_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = 0;
        ssl->specs.block_size            = 0;
        ssl->specs.iv_size               = 0;

        ssl->options.usingPSK_cipher     = 1;
        break;
#endif

#ifdef BUILD_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256
    case TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256
    case TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_DHE_RSA_WITH_AES_128_CBC_SHA
    case TLS_DHE_RSA_WITH_AES_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_DHE_RSA_WITH_AES_256_CBC_SHA
    case TLS_DHE_RSA_WITH_AES_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_256_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_HC_128_MD5
    case TLS_RSA_WITH_HC_128_MD5 :
        ssl->specs.bulk_cipher_algorithm = cyassl_hc128;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = md5_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = MD5_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_MD5;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = HC_128_KEY_SIZE;
        ssl->specs.block_size            = 0;
        ssl->specs.iv_size               = HC_128_IV_SIZE;

        break;
#endif
            
#ifdef BUILD_TLS_RSA_WITH_HC_128_SHA
        case TLS_RSA_WITH_HC_128_SHA :
            ssl->specs.bulk_cipher_algorithm = cyassl_hc128;
            ssl->specs.cipher_type           = stream;
            ssl->specs.mac_algorithm         = sha_mac;
            ssl->specs.kea                   = rsa_kea;
            ssl->specs.sig_algo              = rsa_sa_algo;
            ssl->specs.hash_size             = SHA_DIGEST_SIZE;
            ssl->specs.pad_size              = PAD_SHA;
            ssl->specs.static_ecdh           = 0;
            ssl->specs.key_size              = HC_128_KEY_SIZE;
            ssl->specs.block_size            = 0;
            ssl->specs.iv_size               = HC_128_IV_SIZE;
            
            break;
#endif

#ifdef BUILD_TLS_RSA_WITH_HC_128_B2B256
        case TLS_RSA_WITH_HC_128_B2B256:
            ssl->specs.bulk_cipher_algorithm = cyassl_hc128;
            ssl->specs.cipher_type           = stream;
            ssl->specs.mac_algorithm         = blake2b_mac;
            ssl->specs.kea                   = rsa_kea;
            ssl->specs.sig_algo              = rsa_sa_algo;
            ssl->specs.hash_size             = BLAKE2B_256;
            ssl->specs.pad_size              = PAD_SHA;
            ssl->specs.static_ecdh           = 0;
            ssl->specs.key_size              = HC_128_KEY_SIZE;
            ssl->specs.block_size            = 0;
            ssl->specs.iv_size               = HC_128_IV_SIZE;
            
            break;
#endif

#ifdef BUILD_TLS_RSA_WITH_AES_128_CBC_B2B256
        case TLS_RSA_WITH_AES_128_CBC_B2B256:
            ssl->specs.bulk_cipher_algorithm = cyassl_aes;
            ssl->specs.cipher_type           = block;
            ssl->specs.mac_algorithm         = blake2b_mac;
            ssl->specs.kea                   = rsa_kea;
            ssl->specs.sig_algo              = rsa_sa_algo;
            ssl->specs.hash_size             = BLAKE2B_256;
            ssl->specs.pad_size              = PAD_SHA;
            ssl->specs.static_ecdh           = 0;
            ssl->specs.key_size              = AES_128_KEY_SIZE;
            ssl->specs.iv_size               = AES_IV_SIZE;
            ssl->specs.block_size            = AES_BLOCK_SIZE;
            
            break;
#endif

#ifdef BUILD_TLS_RSA_WITH_AES_256_CBC_B2B256
        case TLS_RSA_WITH_AES_256_CBC_B2B256:
            ssl->specs.bulk_cipher_algorithm = cyassl_aes;
            ssl->specs.cipher_type           = block;
            ssl->specs.mac_algorithm         = blake2b_mac;
            ssl->specs.kea                   = rsa_kea;
            ssl->specs.sig_algo              = rsa_sa_algo;
            ssl->specs.hash_size             = BLAKE2B_256;
            ssl->specs.pad_size              = PAD_SHA;
            ssl->specs.static_ecdh           = 0;
            ssl->specs.key_size              = AES_256_KEY_SIZE;
            ssl->specs.iv_size               = AES_IV_SIZE;
            ssl->specs.block_size            = AES_BLOCK_SIZE;
            
            break;
#endif

#ifdef BUILD_TLS_RSA_WITH_RABBIT_SHA
    case TLS_RSA_WITH_RABBIT_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_rabbit;
        ssl->specs.cipher_type           = stream;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = RABBIT_KEY_SIZE;
        ssl->specs.block_size            = 0;
        ssl->specs.iv_size               = RABBIT_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_AES_128_GCM_SHA256
    case TLS_RSA_WITH_AES_128_GCM_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
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
        ssl->specs.aead_mac_size         = AES_GCM_AUTH_SZ;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_AES_256_GCM_SHA384
    case TLS_RSA_WITH_AES_256_GCM_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = rsa_kea;
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

#ifdef BUILD_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256
    case TLS_DHE_RSA_WITH_AES_128_GCM_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
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

#ifdef BUILD_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384
    case TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes_gcm;
        ssl->specs.cipher_type           = aead;
        ssl->specs.mac_algorithm         = sha384_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
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

#ifdef BUILD_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA
    case TLS_RSA_WITH_CAMELLIA_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_camellia;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = CAMELLIA_128_KEY_SIZE;
        ssl->specs.block_size            = CAMELLIA_BLOCK_SIZE;
        ssl->specs.iv_size               = CAMELLIA_IV_SIZE;

        break;
#endif
    
#ifdef BUILD_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA
    case TLS_RSA_WITH_CAMELLIA_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_camellia;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = CAMELLIA_256_KEY_SIZE;
        ssl->specs.block_size            = CAMELLIA_BLOCK_SIZE;
        ssl->specs.iv_size               = CAMELLIA_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256
    case TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_camellia;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = CAMELLIA_128_KEY_SIZE;
        ssl->specs.block_size            = CAMELLIA_BLOCK_SIZE;
        ssl->specs.iv_size               = CAMELLIA_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256
    case TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_camellia;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = rsa_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = CAMELLIA_256_KEY_SIZE;
        ssl->specs.block_size            = CAMELLIA_BLOCK_SIZE;
        ssl->specs.iv_size               = CAMELLIA_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA
    case TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_camellia;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = CAMELLIA_128_KEY_SIZE;
        ssl->specs.block_size            = CAMELLIA_BLOCK_SIZE;
        ssl->specs.iv_size               = CAMELLIA_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA
    case TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_camellia;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = CAMELLIA_256_KEY_SIZE;
        ssl->specs.block_size            = CAMELLIA_BLOCK_SIZE;
        ssl->specs.iv_size               = CAMELLIA_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256
    case TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_camellia;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = CAMELLIA_128_KEY_SIZE;
        ssl->specs.block_size            = CAMELLIA_BLOCK_SIZE;
        ssl->specs.iv_size               = CAMELLIA_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256
    case TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256 :
        ssl->specs.bulk_cipher_algorithm = cyassl_camellia;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha256_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
        ssl->specs.sig_algo              = rsa_sa_algo;
        ssl->specs.hash_size             = SHA256_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = CAMELLIA_256_KEY_SIZE;
        ssl->specs.block_size            = CAMELLIA_BLOCK_SIZE;
        ssl->specs.iv_size               = CAMELLIA_IV_SIZE;

        break;
#endif

#ifdef BUILD_TLS_DH_anon_WITH_AES_128_CBC_SHA
    case TLS_DH_anon_WITH_AES_128_CBC_SHA :
        ssl->specs.bulk_cipher_algorithm = cyassl_aes;
        ssl->specs.cipher_type           = block;
        ssl->specs.mac_algorithm         = sha_mac;
        ssl->specs.kea                   = diffie_hellman_kea;
        ssl->specs.sig_algo              = anonymous_sa_algo;
        ssl->specs.hash_size             = SHA_DIGEST_SIZE;
        ssl->specs.pad_size              = PAD_SHA;
        ssl->specs.static_ecdh           = 0;
        ssl->specs.key_size              = AES_128_KEY_SIZE;
        ssl->specs.block_size            = AES_BLOCK_SIZE;
        ssl->specs.iv_size               = AES_IV_SIZE;

        ssl->options.usingAnon_cipher    = 1;
        break;
#endif

    default:
        CYASSL_MSG("Unsupported cipher suite, SetCipherSpecs");
        return UNSUPPORTED_SUITE;
    }
