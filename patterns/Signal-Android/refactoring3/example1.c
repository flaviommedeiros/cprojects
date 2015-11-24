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

		case TLSEXT_TYPE_user_mapping:
		extname = "user mapping";
		break;

		case TLSEXT_TYPE_client_authz:
		extname = "client authz";
		break;

		case TLSEXT_TYPE_server_authz:
		extname = "server authz";
		break;

		case TLSEXT_TYPE_cert_type:
		extname = "cert type";
		break;

		case TLSEXT_TYPE_elliptic_curves:
		extname = "elliptic curves";
		break;

		case TLSEXT_TYPE_ec_point_formats:
		extname = "EC point formats";
		break;

		case TLSEXT_TYPE_srp:
		extname = "SRP";
		break;

		case TLSEXT_TYPE_signature_algorithms:
		extname = "signature algorithms";
		break;

		case TLSEXT_TYPE_use_srtp:
		extname = "use SRTP";
		break;

		case TLSEXT_TYPE_heartbeat:
		extname = "heartbeat";
		break;

		case TLSEXT_TYPE_session_ticket:
		extname = "session ticket";
		break;

		case TLSEXT_TYPE_renegotiate: 
		extname = "renegotiation info";
		break;

#ifdef TLSEXT_TYPE_opaque_prf_input
		case TLSEXT_TYPE_opaque_prf_input:
		extname = "opaque PRF input";
		break;
#endif
#ifdef TLSEXT_TYPE_next_proto_neg
		case TLSEXT_TYPE_next_proto_neg:
		extname = "next protocol";
		break;
#endif

		case TLSEXT_TYPE_padding:
		extname = "TLS padding";
		break;

		default:
		extname = "unknown";
		break;

		}
