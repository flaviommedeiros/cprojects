#ifdef WITH_SSL
if (client->ssl) {
		ret = ssl_read(client, buf, sizeof(buf));
	} else 
#endif /* WITH_SSL */
	{
		ret = read(client->sock_fd, buf, sizeof(buf));
	}
