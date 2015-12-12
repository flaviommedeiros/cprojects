if (entry->d_name[0] == filename[0]
#if defined(__SVR4) || defined(__linux__)
		    && strlen(entry->d_name) >= filename_len
#else
		    && entry->d_namlen >= filename_len
#endif
		    && strncmp(entry->d_name, filename,
			filename_len) == 0)
			break;
