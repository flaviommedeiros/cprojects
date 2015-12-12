if (STRNEQUAL(url, HTTP_URL)
#ifdef WITH_SSL
	    || STRNEQUAL(url, HTTPS_URL)
#endif
	    || STRNEQUAL(url, FILE_URL))
		return (fetch_url(url, NULL, NULL, NULL));
