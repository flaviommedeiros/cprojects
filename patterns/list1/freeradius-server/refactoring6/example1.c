if ((fr_ipaddr_cmp(&old->ipaddr, &client->ipaddr) == 0) &&
		    (old->ipaddr.prefix == client->ipaddr.prefix) &&
		    namecmp(longname) && namecmp(secret) &&
		    namecmp(shortname) && namecmp(nas_type) &&
		    namecmp(login) && namecmp(password) && namecmp(server) &&
#ifdef WITH_DYNAMIC_CLIENTS
		    (old->lifetime == client->lifetime) &&
		    namecmp(client_server) &&
#endif
#ifdef WITH_COA
		    namecmp(coa_name) &&
		    (old->coa_server == client->coa_server) &&
		    (old->coa_pool == client->coa_pool) &&
#endif
		    (old->message_authenticator == client->message_authenticator)) {
			WARN("Ignoring duplicate client %s", client->longname);
			client_free(client);
			return true;
		}
