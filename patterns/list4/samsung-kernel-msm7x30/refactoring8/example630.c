static const char types[MIGRATE_TYPES] = {
		[MIGRATE_UNMOVABLE]	= 'U',
		[MIGRATE_RECLAIMABLE]	= 'E',
		[MIGRATE_MOVABLE]	= 'M',
		[MIGRATE_RESERVE]	= 'R',
#ifdef CONFIG_CMA
		[MIGRATE_CMA]		= 'C',
#endif
		[MIGRATE_ISOLATE]	= 'I',
	};
