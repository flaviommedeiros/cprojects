if( params->tag != MBEDTLS_ASN1_OID
#if defined(MBEDTLS_PK_PARSE_EC_EXTENDED)
            && params->tag != ( MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE )
#endif
            )
    {
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );
    }
