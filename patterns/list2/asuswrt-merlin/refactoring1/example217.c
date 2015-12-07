if (handler->input != NULL) {
	ret = handler->input(&out->content[out->use], &written,
	                     in->content, &toconv);
	xmlBufferShrink(in, toconv);
	out->use += written;
	out->content[out->use] = 0;
    }
#ifdef LIBXML_ICONV_ENABLED
    else if (handler->iconv_in != NULL) {
	ret = xmlIconvWrapper(handler->iconv_in, &out->content[out->use],
	                      &written, in->content, &toconv);
	xmlBufferShrink(in, toconv);
	out->use += written;
	out->content[out->use] = 0;
	if (ret == -1) ret = -3;
    }
#endif
