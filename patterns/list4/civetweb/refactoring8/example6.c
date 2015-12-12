static duk_number_list_entry poll_consts[] = {
	{ "POLLIN", (double) POLLIN },
	{ "POLLPRI", (double) POLLPRI },
	{ "POLLOUT", (double) POLLOUT },
#if 0
	/* Linux 2.6.17 and upwards, requires _GNU_SOURCE etc, not added
	 * now because we don't use it.
	 */
	{ "POLLRDHUP", (double) POLLRDHUP },
#endif
	{ "POLLERR", (double) POLLERR },
	{ "POLLHUP", (double) POLLHUP },
	{ "POLLNVAL", (double) POLLNVAL },
	{ NULL, 0.0 }
};
