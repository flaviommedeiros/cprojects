switch (tls_session->info.version) {
	case SSL2_VERSION:
		str_version = "SSL 2.0 ";
		break;

	case SSL3_VERSION:
		str_version = "SSL 3.0 ";
		break;

	case TLS1_VERSION:
		str_version = "TLS 1.0 ";
		break;

#ifdef TLS1_1_VERSION
	case TLS1_1_VERSION:
		str_version = "TLS 1.1 ";
		break;
#endif
#ifdef TLS1_2_VERSION
	case TLS1_2_VERSION:
		str_version = "TLS 1.2 ";
		break;
#endif
#ifdef TLS1_3_VERSON
	case TLS1_3_VERSION:
		str_version = "TLS 1.3 ";
		break;
#endif

	default:
		if (tls_session->info.version) {
			sprintf(buffer, "UNKNOWN TLS VERSION 0x%04x", tls_session->info.version);
			str_version = buffer;
		} else {
			str_version = "";
		}
		break;
	}
