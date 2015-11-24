if (++inst->sincesync >= inst->sync_after
#ifdef HAVE_PTHREAD_D
	    && (pthread_mutex_trylock(&inst->mutex)) == 0
#endif
	   ) {
		int r;

		inst->sincesync = 0;

		radlog(L_DBG,
			"mod_post_auth(): syncing with radacct table");

		r = (nvp_freeclosed(inst, sqlsock) && nvp_syncfree(inst, sqlsock));

#ifdef HAVE_PTHREAD_D
		pthread_mutex_unlock(&inst->mutex);
#endif

		if (!r) {
			radlog(L_ERR,
				"mod_post_auth(): synchronization failed");
			fr_connection_release(inst->sql_inst->pool, sqlsock);
			return RLM_MODULE_FAIL;
		}
	}
