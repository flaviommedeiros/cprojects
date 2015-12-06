if (home->dual
#ifdef WITH_TLS
	    && !home->tls
#endif
) {
		home_server_t *home2 = talloc(talloc_parent(home), home_server_t);

		memcpy(home2, home, sizeof(*home2));

		home2->type = HOME_TYPE_ACCT;
		home2->dual = true;
		home2->port++;

		home2->ping_user_password = NULL;
		home2->cs = home->cs;
		home2->parent_server = home->parent_server;

		if (!home_server_insert(home2, home->cs)) {
			talloc_free(home2);
			return false;
		}
	}
