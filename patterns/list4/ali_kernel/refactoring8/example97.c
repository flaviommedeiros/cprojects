static int rc_paranoia_check(struct riscom_port const *port,
				    char *name, const char *routine)
{
#ifdef RISCOM_PARANOIA_CHECK
	static const char badmagic[] = KERN_INFO
		"rc: Warning: bad riscom port magic number for device %s in %s\n";
	static const char badinfo[] = KERN_INFO
		"rc: Warning: null riscom port for device %s in %s\n";

	if (!port) {
		printk(badinfo, name, routine);
		return 1;
	}
	if (port->magic != RISCOM8_MAGIC) {
		printk(badmagic, name, routine);
		return 1;
	}
#endif
	return 0;
}
