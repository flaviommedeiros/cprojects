static char * const migratetype_names[MIGRATE_TYPES] = {
	"Unmovable",
	"Reclaimable",
	"Movable",
	"Reserve",
#ifdef CONFIG_CMA
	"CMA",
#endif
	"Isolate",
};
