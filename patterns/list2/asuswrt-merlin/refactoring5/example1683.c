#ifdef HAVE_REPLICATION_THREADS
if (F_ISSET(env, ENV_THREAD) &&
		    rep->my_addr.host != INVALID_ROFF) {
			if ((ret = __repmgr_autostart(env)) != 0)
				return (ret);
		} else
#endif
		{
#if !defined(DEBUG_ROP) && !defined(DEBUG_WOP)
			__db_errx(env, "%s %s",
			    "Non-replication DB_ENV handle attempting",
			    "to modify a replicated environment");
			return (EINVAL);
#endif
		}
