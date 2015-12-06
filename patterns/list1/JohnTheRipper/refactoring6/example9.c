if (alt == &fmt_crypt &&
		    fmt_list != &fmt_crypt /* not forced */ &&
#ifdef __sun
		    strncmp(*ciphertext, "$md5$", 5) &&
		    strncmp(*ciphertext, "$md5,", 5) &&
#endif
		    strncmp(*ciphertext, "$5$", 3) &&
		    strncmp(*ciphertext, "$6$", 3))
			continue;
