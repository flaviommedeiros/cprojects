#ifdef HAVE_DHCP6
if (daemon->doing_dhcp6 || daemon->relay6)
	poll_listen(daemon->dhcp6fd, POLLIN);
