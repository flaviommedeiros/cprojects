#ifdef CONFIG_CMA
if (migratetype == MIGRATE_MOVABLE && !zone->cma_alloc)
		page = __rmqueue_smallest(zone, order, MIGRATE_CMA);
