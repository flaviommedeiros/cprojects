# ifdef _LIBC
if (__wcscoll (range_start_char, str_buf+2) <= 0
			&& __wcscoll (str_buf+2, range_end_char) <= 0)
# else
		    if (wcscoll (range_start_char, str_buf+2) <= 0
			&& wcscoll (str_buf+2, range_end_char) <= 0)
# endif
		      goto char_set_matched;
