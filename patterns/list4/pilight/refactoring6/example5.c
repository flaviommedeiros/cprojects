if( params->tag != ASN1_OID
#if defined(POLARSSL_PK_PARSE_EC_EXTENDED)
            && params->tag != ( ASN1_CONSTRUCTED | ASN1_SEQUENCE )
#endif
            )
    {
        return( POLARSSL_ERR_PK_KEY_INVALID_FORMAT +
                POLARSSL_ERR_ASN1_UNEXPECTED_TAG );
    }
