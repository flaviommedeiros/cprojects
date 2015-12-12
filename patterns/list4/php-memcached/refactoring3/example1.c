switch (op) {
		case MEMC_OP_SET:
			if (!server_key) {
				status = memcached_set(m_obj->memc, key, key_len, payload, payload_len, expiration, flags);
			} else {
				status = memcached_set_by_key(m_obj->memc, server_key, server_key_len, key,
										  key_len, payload, payload_len, expiration, flags);
			}
			break;
#ifdef HAVE_MEMCACHED_TOUCH
		case MEMC_OP_TOUCH:
			if (!server_key) {
				status = memcached_touch(m_obj->memc, key, key_len, expiration);
			} else {
				status = memcached_touch_by_key(m_obj->memc, server_key, server_key_len, key,
										  key_len, expiration);
			}
			break;
#endif
		case MEMC_OP_ADD:
			if (!server_key) {
				status = memcached_add(m_obj->memc, key, key_len, payload, payload_len, expiration, flags);
			} else {
				status = memcached_add_by_key(m_obj->memc, server_key, server_key_len, key,
										  key_len, payload, payload_len, expiration, flags);
			}
			break;

		case MEMC_OP_REPLACE:
			if (!server_key) {
				status = memcached_replace(m_obj->memc, key, key_len, payload, payload_len, expiration, flags);
			} else {
				status = memcached_replace_by_key(m_obj->memc, server_key, server_key_len, key,
										      key_len, payload, payload_len, expiration, flags);
			}
			break;

		case MEMC_OP_APPEND:
			if (!server_key) {
				status = memcached_append(m_obj->memc, key, key_len, payload, payload_len, expiration, flags);
			} else {
				status = memcached_append_by_key(m_obj->memc, server_key, server_key_len, key,
											 key_len, payload, payload_len, expiration, flags);
			}
			break;

		case MEMC_OP_PREPEND:
			if (!server_key) {
				status = memcached_prepend(m_obj->memc, key, key_len, payload, payload_len, expiration, flags);
			} else {
				status = memcached_prepend_by_key(m_obj->memc, server_key, server_key_len, key,
											  key_len, payload, payload_len, expiration, flags);
			}
			break;

		default:
			/* not reached */
			status = 0;
			assert(0);
			break;
	}
