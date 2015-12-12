switch (serializer) {

		/*
			Igbinary serialization
		*/
#ifdef HAVE_MEMCACHED_IGBINARY
		case SERIALIZER_IGBINARY:
			if (igbinary_serialize((uint8_t **) &buf->c, &buf->len, value TSRMLS_CC) != 0) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "could not serialize value with igbinary");
				return 0;
			}
			MEMC_VAL_SET_TYPE(*flags, MEMC_VAL_IS_IGBINARY);
			break;
#endif

		/*
			JSON serialization
		*/
#ifdef HAVE_JSON_API
		case SERIALIZER_JSON:
		case SERIALIZER_JSON_ARRAY:
		{
#if HAVE_JSON_API_5_2
			php_json_encode(buf, value TSRMLS_CC);
#elif HAVE_JSON_API_5_3
			php_json_encode(buf, value, 0 TSRMLS_CC); /* options */
#endif
			MEMC_VAL_SET_TYPE(*flags, MEMC_VAL_IS_JSON);
		}
			break;
#endif

		/*
			msgpack serialization
		*/
#ifdef HAVE_MEMCACHED_MSGPACK
		case SERIALIZER_MSGPACK:
			php_msgpack_serialize(buf, value TSRMLS_CC);
			if (!buf->c) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "could not serialize value with msgpack");
				return 0;
			}
			MEMC_VAL_SET_TYPE(*flags, MEMC_VAL_IS_MSGPACK);
			break;
#endif

		/*
			PHP serialization
		*/
		default:
		{
			php_serialize_data_t var_hash;
			PHP_VAR_SERIALIZE_INIT(var_hash);
			php_var_serialize(buf, &value, &var_hash TSRMLS_CC);
			PHP_VAR_SERIALIZE_DESTROY(var_hash);

			if (!buf->c) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "could not serialize value");
				return 0;
			}
			MEMC_VAL_SET_TYPE(*flags, MEMC_VAL_IS_SERIALIZED);
		}
			break;
	}
