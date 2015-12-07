#ifdef HAVE_EXTRA_DEBUG
if (line && func && file)
		g_string_printf(gstr, "(code=%i) %s,%d ", (code?code:(*e?(*e)->code:0)), func, line);
	else
#endif
		g_string_printf(gstr, "(code=%i) - ", (code?code:(*e?(*e)->code:0)));
