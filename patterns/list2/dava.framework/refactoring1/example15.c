if (handler->output != NULL) {
	    ret = handler->output(&out->content[out->use], &written,
				  NULL, &toconv);
	    if (ret >= 0) { /* Gennady: check return value */
		out->use += written;
		out->content[out->use] = 0;
	    }
	}
#ifdef LIBXML_ICONV_ENABLED
	else if (handler->iconv_out != NULL) {
	    ret = xmlIconvWrapper(handler->iconv_out, &out->content[out->use],
				  &written, NULL, &toconv);
	    out->use += written;
	    out->content[out->use] = 0;
	}
#endif
