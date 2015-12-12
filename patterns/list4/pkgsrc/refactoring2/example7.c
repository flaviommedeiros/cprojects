#ifdef S_ISLNK
if (!physical || !(pwd = get_phys_path(Xstring(xs, xp))))
#endif /* S_ISLNK */
		pwd = Xstring(xs, xp);
