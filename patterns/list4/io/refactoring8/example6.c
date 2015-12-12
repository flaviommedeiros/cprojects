IoMethodTable methodTable[] = {
	{"check", IoCollector_check},
	{"checkObjectPointers", IoCollector_checkObjectPointers},
	{"setDebug", IoCollector_setDebug},
	{"collect", IoCollector_collect},

	{"setMarksPerAlloc", IoCollector_setMarksPerAlloc},
	{"marksPerAlloc", IoCollector_marksPerAlloc},

	{"setAllocatedStep", IoCollector_setAllocatedStep},
	{"allocatedStep", IoCollector_allocatedStep},

	{"allObjects", IoCollector_allObjects},
	{"showStats", IoCollector_showStats},
	{"maxAllocatedBytes", IoCollector_maxAllocatedBytes},
	{"resetMaxAllocatedBytes", IoCollector_resetMaxAllocatedBytes},
	{"timeUsed", IoCollector_timeUsed},
	
	{"objectWithUniqueId", IoCollector_objectWithUniqueId},
	{"dirtyObjects", IoCollector_dirtyObjects},
	{"cleanAllObjects", IoCollector_cleanAllObjects},
	{"checkMemory", IoCollector_checkMemory},
	{"setSafeModeOn", IoCollector_setSafeModeOn},
#ifdef COLLECTOR_USE_NONINCREMENTAL_MARK_SWEEP
	{"setAllocsPerSweep", IoCollector_setAllocsPerSweep},
	{"allocsPerSweep", IoCollector_allocsPerSweep},
#endif
	{NULL, NULL},
	};
