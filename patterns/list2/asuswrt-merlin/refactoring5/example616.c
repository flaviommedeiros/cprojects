#ifdef CONFIG_TEST
if (key_buf_size != 0) {
			(void)__os_malloc(
			    NULL, (size_t)key_buf_size, &key.data);
			key.ulen = (u_int32_t)key_buf_size;
			key.flags |= DB_DBT_USERMEM;
		} else
#endif
			key.flags |= DB_DBT_MALLOC;
