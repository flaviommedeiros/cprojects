#ifdef HAVE_MEMCACHED_MSGPACK
if (Z_LVAL_P(value) == SERIALIZER_MSGPACK) {
				m_obj->serializer = SERIALIZER_MSGPACK;
			} else
#endif
			/* php serializer */
			if (Z_LVAL_P(value) == SERIALIZER_PHP) {
				m_obj->serializer = SERIALIZER_PHP;
			} else {
				m_obj->serializer = SERIALIZER_PHP;
				i_obj->rescode = MEMCACHED_INVALID_ARGUMENTS;
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "invalid serializer provided");
				return 0;
			}
