#ifndef NO_PTHREADS
if (use_threads) {
		add_work(opt, GREP_SOURCE_FILE, buf.buf, filename, filename);
		strbuf_release(&buf);
		return 0;
	} else
#endif
	{
		struct grep_source gs;
		int hit;

		grep_source_init(&gs, GREP_SOURCE_FILE, buf.buf, filename, filename);
		strbuf_release(&buf);
		hit = grep_source(opt, &gs);

		grep_source_clear(&gs);
		return hit;
	}
