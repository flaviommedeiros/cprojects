if ((ctdb_data.dptr == NULL) ||
	    (ctdb_data.dsize < sizeof(struct ctdb_ltdb_header)) ||
	    ((struct ctdb_ltdb_header *)ctdb_data.dptr)->dmaster != get_my_vnn()
#if 0
	    || (random() % 2 != 0)
#endif
) {
		SAFE_FREE(ctdb_data.dptr);
		tdb_chainunlock(ctx->wtdb->tdb, key);
		talloc_set_destructor(result, NULL);

		migrate_attempts += 1;

		DEBUG(10, ("ctdb_data.dptr = %p, dmaster = %u (%u)\n",
			   ctdb_data.dptr, ctdb_data.dptr ?
			   ((struct ctdb_ltdb_header *)ctdb_data.dptr)->dmaster : -1,
			   get_my_vnn()));

		status = ctdbd_migrate(messaging_ctdbd_connection(),ctx->db_id, key);
		if (!NT_STATUS_IS_OK(status)) {
			DEBUG(5, ("ctdb_migrate failed: %s\n",
				  nt_errstr(status)));
			TALLOC_FREE(result);
			return NULL;
		}
		/* now its migrated, try again */
		goto again;
	}
