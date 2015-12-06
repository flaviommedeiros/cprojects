switch (type) {
	case HTTP_BODY_NONE:
		if (rest_request_config_body(instance, section, request, handle,
					     NULL) < 0) {
			return -1;
		}

		break;

	case HTTP_BODY_CUSTOM_XLAT:
	{
		rest_custom_data_t *data;
		char *expanded = NULL;

		if (radius_axlat(&expanded, request, section->data, NULL, NULL) < 0) return -1;

		data = talloc_zero(request, rest_custom_data_t);
		data->p = expanded;
		data->start = expanded;
		data->len = strlen(expanded);	// Fix me when we do binary xlat

		/* Use the encoder specific pointer to store the data we need to encode */
		ctx->request.encoder = data;
		if (rest_request_config_body(instance, section, request, handle,
					     rest_encode_custom) < 0) {
			TALLOC_FREE(ctx->request.encoder);
			return -1;
		}

		break;
	}

	case HTTP_BODY_CUSTOM_LITERAL:
	{
		rest_custom_data_t *data;

		data = talloc_zero(request, rest_custom_data_t);
		data->p = section->data;
		data->start = section->data;
		data->len = strlen(section->data);

		/* Use the encoder specific pointer to store the data we need to encode */
		ctx->request.encoder = data;
		if (rest_request_config_body(instance, section, request, handle,
					     rest_encode_custom) < 0) {
			TALLOC_FREE(ctx->request.encoder);
			return -1;
		}
	}
		break;

#ifdef HAVE_JSON
	case HTTP_BODY_JSON:
		rest_request_init(request, &ctx->request, true);

		if (rest_request_config_body(instance, section, request, handle,
					     rest_encode_json) < 0) {
			return -1;
		}

		break;
#endif

	case HTTP_BODY_POST:
		rest_request_init(request, &ctx->request, false);

		if (rest_request_config_body(instance, section, request, handle,
					     rest_encode_post) < 0) {
			return -1;
		}

		break;

	default:
		rad_assert(0);
	}
