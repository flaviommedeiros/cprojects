#if defined(POLARSSL_REMOVE_ARC4_CIPHERSUITES)
if( ( cs_info = ssl_ciphersuite_from_id( *p ) ) != NULL &&
                cs_info->cipher != POLARSSL_CIPHER_ARC4_128 )
#else
            if( ssl_ciphersuite_from_id( *p ) != NULL )
#endif
                *(q++) = *p;
