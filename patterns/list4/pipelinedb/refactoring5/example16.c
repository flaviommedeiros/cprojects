#ifdef USE_SSL
if (port->ssl)
				ereport(LOG,
						(errmsg("connection authorized: user=%s database=%s SSL enabled (protocol=%s, cipher=%s, compression=%s)",
								port->user_name, port->database_name, SSL_get_version(port->ssl), SSL_get_cipher(port->ssl),
								SSL_get_current_compression(port->ssl) ? _("on") : _("off"))));
			else
#endif
				ereport(LOG,
						(errmsg("connection authorized: user=%s database=%s",
								port->user_name, port->database_name)));
