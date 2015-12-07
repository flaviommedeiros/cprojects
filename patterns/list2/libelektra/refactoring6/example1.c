if (stat != yajl_status_ok
#if YAJL_MAJOR == 1
			&& stat != yajl_status_insufficient_data
#endif
			)
		{
			unsigned char * str = yajl_get_error(hand, 1,
					fileData, rd);
			ELEKTRA_SET_ERROR(77, parentKey, (char*)str);
			yajl_free_error(hand, str);
			yajl_free (hand);
			fclose (fileHandle);

			return -1;
		}
