if ((t_ret = __db_salvage_duptree(dbp,
			    vdp, bo->pgno, &dbt, handle, callback,
			    flags | DB_SA_SKIPFIRSTKEY
#ifdef HAVE_COMPRESSION
			    | (last_key == NULL ? DB_SA_UNKNOWNKEY : 0)
#endif
			    )) != 0 && ret == 0)
				ret = t_ret;
