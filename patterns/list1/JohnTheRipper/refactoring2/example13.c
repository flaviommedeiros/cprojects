#if SSE_GROUP_SZ_SHA512
if (psalt->hash_type != IS_SHA512)
#endif
		{
			strncpy((char*)key, (char*)key_buffer[i], 64);

			/* process keyfile(s) */
			if (psalt->nkeyfiles) {
				apply_keyfiles(key, 64, psalt->nkeyfiles);
				ksz = 64;
			}
		}
