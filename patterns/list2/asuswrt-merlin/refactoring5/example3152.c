#ifdef HAVE_PARTITION
if (F_ISSET(dbc, DBC_PARTITIONED))
		ret = __partc_get(dbc, key, data, flags);
	else
#endif
		ret = __dbc_get(dbc, key, data, flags);
