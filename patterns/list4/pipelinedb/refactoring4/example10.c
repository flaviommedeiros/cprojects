#ifdef HAVE_IPV6
if (remoteaddr.sin6_port != htons(port->hba->radiusport))
#else
		if (remoteaddr.sin_port != htons(port->hba->radiusport))
#endif
		{
#ifdef HAVE_IPV6
			ereport(LOG,
				  (errmsg("RADIUS response was sent from incorrect port: %d",
						  ntohs(remoteaddr.sin6_port))));
#else
			ereport(LOG,
				  (errmsg("RADIUS response was sent from incorrect port: %d",
						  ntohs(remoteaddr.sin_port))));
#endif
			continue;
		}
