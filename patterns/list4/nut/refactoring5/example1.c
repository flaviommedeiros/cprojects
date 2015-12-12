#ifdef WITH_SSL
if (client->ssl) {
		res = ssl_write(client, ans, len);
	} else 
#endif /* WITH_SSL */
	{
		res = write(client->sock_fd, ans, len);
	}
