static const int ciphersuite_preference[] =
{
#if defined(MBEDTLS_SSL_CIPHERSUITES)
    MBEDTLS_SSL_CIPHERSUITES,
#else
    /* All AES-256 ephemeral suites */
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,
    MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CCM,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CCM,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384,
    MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CCM_8,

    /* All CAMELLIA-256 ephemeral suites */
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384,
    MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384,
    MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384,
    MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384,
    MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256,
    MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA,

    /* All AES-128 ephemeral suites */
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,
    MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CCM,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CCM,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8,
    MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CCM_8,

    /* All CAMELLIA-128 ephemeral suites */
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256,
    MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256,
    MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256,
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256,
    MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256,
    MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256,
    MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA,

    /* All remaining >= 128-bit ephemeral suites */
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA,
    MBEDTLS_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA,
    MBEDTLS_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA,

    /* The PSK ephemeral suites */
    MBEDTLS_TLS_DHE_PSK_WITH_AES_256_GCM_SHA384,
    MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CCM,
    MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384,
    MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CBC_SHA384,
    MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_256_GCM_SHA384,
    MBEDTLS_TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC_SHA384,
    MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_256_CBC_SHA384,
    MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CCM_8,

    MBEDTLS_TLS_DHE_PSK_WITH_AES_128_GCM_SHA256,
    MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CCM,
    MBEDTLS_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_128_GCM_SHA256,
    MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_128_CBC_SHA256,
    MBEDTLS_TLS_ECDHE_PSK_WITH_CAMELLIA_128_CBC_SHA256,
    MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CCM_8,

    MBEDTLS_TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA,
    MBEDTLS_TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA,

    /* The ECJPAKE suite */
    MBEDTLS_TLS_ECJPAKE_WITH_AES_128_CCM_8,

    /* All AES-256 suites */
    MBEDTLS_TLS_RSA_WITH_AES_256_GCM_SHA384,
    MBEDTLS_TLS_RSA_WITH_AES_256_CCM,
    MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA256,
    MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384,
    MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384,
    MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_RSA_WITH_AES_256_CCM_8,

    /* All CAMELLIA-256 suites */
    MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384,
    MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256,
    MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA,
    MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384,
    MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384,

    /* All AES-128 suites */
    MBEDTLS_TLS_RSA_WITH_AES_128_GCM_SHA256,
    MBEDTLS_TLS_RSA_WITH_AES_128_CCM,
    MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256,
    MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_RSA_WITH_AES_128_CCM_8,

    /* All CAMELLIA-128 suites */
    MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256,
    MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256,
    MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA,
    MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256,
    MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256,

    /* All remaining >= 128-bit suites */
    MBEDTLS_TLS_RSA_WITH_3DES_EDE_CBC_SHA,
    MBEDTLS_TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA,

    /* The RSA PSK suites */
    MBEDTLS_TLS_RSA_PSK_WITH_AES_256_GCM_SHA384,
    MBEDTLS_TLS_RSA_PSK_WITH_AES_256_CBC_SHA384,
    MBEDTLS_TLS_RSA_PSK_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_256_GCM_SHA384,
    MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_256_CBC_SHA384,

    MBEDTLS_TLS_RSA_PSK_WITH_AES_128_GCM_SHA256,
    MBEDTLS_TLS_RSA_PSK_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_RSA_PSK_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256,
    MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_128_CBC_SHA256,

    MBEDTLS_TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA,

    /* The PSK suites */
    MBEDTLS_TLS_PSK_WITH_AES_256_GCM_SHA384,
    MBEDTLS_TLS_PSK_WITH_AES_256_CCM,
    MBEDTLS_TLS_PSK_WITH_AES_256_CBC_SHA384,
    MBEDTLS_TLS_PSK_WITH_AES_256_CBC_SHA,
    MBEDTLS_TLS_PSK_WITH_CAMELLIA_256_GCM_SHA384,
    MBEDTLS_TLS_PSK_WITH_CAMELLIA_256_CBC_SHA384,
    MBEDTLS_TLS_PSK_WITH_AES_256_CCM_8,

    MBEDTLS_TLS_PSK_WITH_AES_128_GCM_SHA256,
    MBEDTLS_TLS_PSK_WITH_AES_128_CCM,
    MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA256,
    MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA,
    MBEDTLS_TLS_PSK_WITH_CAMELLIA_128_GCM_SHA256,
    MBEDTLS_TLS_PSK_WITH_CAMELLIA_128_CBC_SHA256,
    MBEDTLS_TLS_PSK_WITH_AES_128_CCM_8,

    MBEDTLS_TLS_PSK_WITH_3DES_EDE_CBC_SHA,

    /* RC4 suites */
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_RC4_128_SHA,
    MBEDTLS_TLS_ECDHE_RSA_WITH_RC4_128_SHA,
    MBEDTLS_TLS_ECDHE_PSK_WITH_RC4_128_SHA,
    MBEDTLS_TLS_DHE_PSK_WITH_RC4_128_SHA,
    MBEDTLS_TLS_RSA_WITH_RC4_128_SHA,
    MBEDTLS_TLS_RSA_WITH_RC4_128_MD5,
    MBEDTLS_TLS_ECDH_RSA_WITH_RC4_128_SHA,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_RC4_128_SHA,
    MBEDTLS_TLS_RSA_PSK_WITH_RC4_128_SHA,
    MBEDTLS_TLS_PSK_WITH_RC4_128_SHA,

    /* Weak suites */
    MBEDTLS_TLS_DHE_RSA_WITH_DES_CBC_SHA,
    MBEDTLS_TLS_RSA_WITH_DES_CBC_SHA,

    /* NULL suites */
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_NULL_SHA,
    MBEDTLS_TLS_ECDHE_RSA_WITH_NULL_SHA,
    MBEDTLS_TLS_ECDHE_PSK_WITH_NULL_SHA384,
    MBEDTLS_TLS_ECDHE_PSK_WITH_NULL_SHA256,
    MBEDTLS_TLS_ECDHE_PSK_WITH_NULL_SHA,
    MBEDTLS_TLS_DHE_PSK_WITH_NULL_SHA384,
    MBEDTLS_TLS_DHE_PSK_WITH_NULL_SHA256,
    MBEDTLS_TLS_DHE_PSK_WITH_NULL_SHA,

    MBEDTLS_TLS_RSA_WITH_NULL_SHA256,
    MBEDTLS_TLS_RSA_WITH_NULL_SHA,
    MBEDTLS_TLS_RSA_WITH_NULL_MD5,
    MBEDTLS_TLS_ECDH_RSA_WITH_NULL_SHA,
    MBEDTLS_TLS_ECDH_ECDSA_WITH_NULL_SHA,
    MBEDTLS_TLS_RSA_PSK_WITH_NULL_SHA384,
    MBEDTLS_TLS_RSA_PSK_WITH_NULL_SHA256,
    MBEDTLS_TLS_RSA_PSK_WITH_NULL_SHA,
    MBEDTLS_TLS_PSK_WITH_NULL_SHA384,
    MBEDTLS_TLS_PSK_WITH_NULL_SHA256,
    MBEDTLS_TLS_PSK_WITH_NULL_SHA,

#endif /* MBEDTLS_SSL_CIPHERSUITES */
    0
};