#ifdef HAVE_CURSES
if (for_curses)
	{
		if (opt_show_procs)
			snprintf(buf, bufsz, " %*s: ", -(5 + max_lpdigits), cgpu->proc_repr);
		else
			snprintf(buf, bufsz, " %s: ", cgpu->dev_repr);
	}
	else
#endif
	{
		if (opt_show_procs)
			snprintf(buf, bufsz, "%*s ", -(5 + max_lpdigits), cgpu->proc_repr_ns);
		else
			snprintf(buf, bufsz, "%-5s ", cgpu->dev_repr_ns);
	}
