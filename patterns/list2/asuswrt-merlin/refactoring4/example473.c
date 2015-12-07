#ifdef HOSTS_ACCESS
if (port && !check_privileged_port(addr, proc, prog, port))
	return (FALSE);
