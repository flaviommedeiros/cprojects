if (s->check_type == XZ_CHECK_CRC32) {
				ret = crc32_validate(s, b);
				if (ret != XZ_STREAM_END)
					return ret;
			}
#ifdef XZ_DEC_ANY_CHECK
			else if (!check_skip(s, b)) {
				return XZ_OK;
			}
#endif
