#ifndef NO_PTHREADS
if (use_threads) {
		add_work(opt, GREP_SOURCE_SHA1, pathbuf.buf, path, sha1);
		strbuf_release(&pathbuf);
		return 0;
	} else
#endif
	{
		struct grep_source gs;
		int hit;

		grep_source_init(&gs, GREP_SOURCE_SHA1, pathbuf.buf, path, sha1);
		strbuf_release(&pathbuf);
		hit = grep_source(opt, &gs);

		grep_source_clear(&gs);
		return hit;
	}
