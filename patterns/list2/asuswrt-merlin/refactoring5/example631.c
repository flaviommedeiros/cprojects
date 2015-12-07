#ifdef HAVE_PARTITION
if (DB_IS_PARTITIONED(dbp))
			ret = __part_key_range(dbc, key, kr, flags);
		else
#endif
			ret = __bam_key_range(dbc, key, kr, flags);
