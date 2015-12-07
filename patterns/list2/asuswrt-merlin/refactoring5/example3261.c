#ifndef DISABLE_ZLIB
if (is_compress_recv()) {
		/* decompress */
		ses.payload = buf_decompress(ses.readbuf, len);
		buf_setpos(ses.payload, 0);
		ses.payload_beginning = 0;
		buf_free(ses.readbuf);
	} else 
#endif
	{
		ses.payload = ses.readbuf;
		ses.payload_beginning = ses.payload->pos;
		buf_setlen(ses.payload, ses.payload->pos + len);
		/* copy payload */
		//ses.payload = buf_new(len);
		//memcpy(ses.payload->data, buf_getptr(ses.readbuf, len), len);
		//buf_incrlen(ses.payload, len);
	}
