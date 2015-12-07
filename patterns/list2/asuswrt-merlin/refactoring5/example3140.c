#ifdef CONFIG_TEST
if (data_buf_size != 0) {
			(void)__os_malloc(
			    NULL, (size_t)data_buf_size, &data.data);
			data.ulen = (u_int32_t)data_buf_size;
			data.flags |= DB_DBT_USERMEM;
		} else
#endif
			data.flags |= DB_DBT_MALLOC;
