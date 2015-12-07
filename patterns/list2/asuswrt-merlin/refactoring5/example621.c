#ifdef HAVE_PARTITION
if (DB_IS_PARTITIONED(dbp)) {
			if ((ret = __partc_init(dbc)) != 0)
				goto err;
		} else
#endif
		switch (dbtype) {
		case DB_BTREE:
		case DB_RECNO:
			if ((ret = __bamc_init(dbc, dbtype)) != 0)
				goto err;
			break;
		case DB_HASH:
			if ((ret = __hamc_init(dbc)) != 0)
				goto err;
			break;
		case DB_QUEUE:
			if ((ret = __qamc_init(dbc)) != 0)
				goto err;
			break;
		case DB_UNKNOWN:
		default:
			ret = __db_unknown_type(env, "DB->cursor", dbtype);
			goto err;
		}
