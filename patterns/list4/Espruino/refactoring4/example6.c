#if defined(MBEDTLS_AES_C)
if( use_ret == -(MBEDTLS_ERR_AES_INVALID_KEY_LENGTH) )
        mbedtls_snprintf( buf, buflen, "AES - Invalid key length" );
