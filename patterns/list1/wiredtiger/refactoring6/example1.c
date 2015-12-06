if (read_size == -1
#ifndef _WIN32
	/* Windows automatically translates \r\n -> \n so counts will be off */
	|| (size_t)read_size != buf_size
#endif
	) {
		fprintf(stderr,
		    "wtperf: read unexpected amount from config file\n");
		ret = EINVAL;
		goto err;
	}
