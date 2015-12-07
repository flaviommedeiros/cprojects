if (buffer_is_empty(p->conf.basepath)
#ifdef HAVE_PWD_H
	    && NULL == (pwd = getpwnam(p->username->ptr))
#endif
	    ) {
		/* user not found */
		return HANDLER_GO_ON;
	}
