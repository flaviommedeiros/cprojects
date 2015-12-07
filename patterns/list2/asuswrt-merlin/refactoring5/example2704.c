#ifdef CONFIG_IPV6
if (conf->ipv6)
		data->auth_sock = radius_server_open_socket6(conf->auth_port);
	else
#endif /* CONFIG_IPV6 */
	data->auth_sock = radius_server_open_socket(conf->auth_port);
