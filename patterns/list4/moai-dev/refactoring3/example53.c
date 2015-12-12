switch(type)
		{
		case TLSEXT_TYPE_server_name:
		extname = "server name";
		break;

		case TLSEXT_TYPE_max_fragment_length:
		extname = "max fragment length";
		break;

		case TLSEXT_TYPE_client_certificate_url:
		extname = "client certificate URL";
		break;

		case TLSEXT_TYPE_trusted_ca_keys:
		extname = "trusted CA keys";
		break;

		case TLSEXT_TYPE_truncated_hmac:
		extname = "truncated HMAC";
		break;

		case TLSEXT_TYPE_status_request:
		extname = "status request";
		break;

		case TLSEXT_TYPE_elliptic_curves:
		extname = "elliptic curves";
		break;

		case TLSEXT_TYPE_ec_point_formats:
		extname = "EC point formats";
		break;

		case TLSEXT_TYPE_session_ticket:
		extname = "server ticket";
		break;

		case TLSEXT_TYPE_renegotiate:
		extname = "renegotiate";
		break;

#ifdef TLSEXT_TYPE_opaque_prf_input
		case TLSEXT_TYPE_opaque_prf_input:
		extname = "opaque PRF input";
		break;
#endif

		default:
		extname = "unknown";
		break;

		}
