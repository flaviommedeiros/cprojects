#if defined(MBEDTLS_REMOVE_ARC4_CIPHERSUITES)
if( ( cs_info = mbedtls_ssl_ciphersuite_from_id( *p ) ) != NULL &&
                cs_info->cipher != MBEDTLS_CIPHER_ARC4_128 )
#else
            if( mbedtls_ssl_ciphersuite_from_id( *p ) != NULL )
#endif
                *(q++) = *p;
