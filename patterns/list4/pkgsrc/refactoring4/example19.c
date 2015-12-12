# ifdef HAVE_SYS_ERRLIST
if (err < 0 || err >= sys_nerr)
		shf_snprintf(p = buf, sizeof(buf), "Unknown system error %d",
			err);
	else
		p = sys_errlist[err];
