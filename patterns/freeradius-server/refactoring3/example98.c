switch (ctx->response.type) {
	case HTTP_BODY_NONE:
		return 0;

	case HTTP_BODY_PLAIN:
		ret = rest_decode_plain(instance, section, request, handle, ctx->response.buffer, ctx->response.used);
		break;

	case HTTP_BODY_POST:
		ret = rest_decode_post(instance, section, request, handle, ctx->response.buffer, ctx->response.used);
		break;

#ifdef HAVE_JSON
	case HTTP_BODY_JSON:
		ret = rest_decode_json(instance, section, request, handle, ctx->response.buffer, ctx->response.used);
		break;
#endif

	case HTTP_BODY_UNSUPPORTED:
	case HTTP_BODY_UNAVAILABLE:
	case HTTP_BODY_INVALID:
		return -1;

	default:
		rad_assert(0);
	}
