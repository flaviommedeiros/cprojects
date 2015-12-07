#if MODULE_MAGIC_COOKIE == 0x41503234UL
if(!authorized_personal_only(r->connection->client_ip, conf->rawx_conf->acl))
#else
		if(!authorized_personal_only(r->connection->remote_ip, conf->rawx_conf->acl))
#endif
		{
			return server_create_and_stat_error(conf, r->pool, HTTP_UNAUTHORIZED, 0, "Permission Denied (APO)");
		}
