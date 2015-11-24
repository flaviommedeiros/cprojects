switch (tls_session->info.content_type) {
	case SSL3_RT_CHANGE_CIPHER_SPEC:
		str_content_type = "change_cipher_spec ";
		break;

	case SSL3_RT_ALERT:
		str_content_type = "alert ";
		break;

	case SSL3_RT_HANDSHAKE:
		str_content_type = "handshake ";
		break;

	case SSL3_RT_APPLICATION_DATA:
		str_content_type = "application_data ";
		break;

	case TLS1_RT_HEARTBEAT:
		str_content_type = "heartbeat ";
		break;

#ifdef TLS1_RT_CRYPTO
	case TLS1_RT_CRYPTO:
		str_content_type = "crypto ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_PREMASTER
	case TLS1_RT_CRYPTO_PREMASTER:
		str_content_type = "crypto_premaster ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_CLIENT_RANDOM
	case TLS1_RT_CRYPTO_CLIENT_RANDOM:
		str_content_type = "client_random ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_SERVER_RANDOM
	case TLS1_RT_CRYPTO_SERVER_RANDOM:
		str_content_type = "server_random ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_MASTER
	case TLS1_RT_CRYPTO_MASTER:
		str_content_type = "crypto_master ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_READ
	case TLS1_RT_CRYPTO_READ:
		str_content_type = "crypto_read ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_WRITE
	case TLS1_RT_CRYPTO_WRITE:
		str_content_type = "crypto_write ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_MAC
	case TLS1_RT_CRYPTO_MAC:
		str_content_type = "crypto_mac ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_KEY
	case TLS1_RT_CRYPTO_KEY:
		str_content_type = "crypto_key ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_IV
	case TLS1_RT_CRYPTO_IV:
		str_content_type = "crypto_iv ";
		break;
#endif

#ifdef TLS1_RT_CRYPTO_FIXED_IV
	case TLS1_RT_CRYPTO_FIXED_IV:
		str_content_type = "crypto_fixed_iv ";
		break;
#endif

	default:
		snprintf(content_type, sizeof(content_type), "unknown content type %i", tls_session->info.content_type );
		str_content_type = content_type;
		break;
	}
