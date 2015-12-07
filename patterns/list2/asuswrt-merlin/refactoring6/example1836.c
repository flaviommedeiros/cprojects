if (h->pgno == last_pgno
#ifdef HAVE_FTRUNCATE
		    && do_truncate == 0
#endif
		)
			lflag = DB_FLUSH;
