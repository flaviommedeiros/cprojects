if (LWLockConditionalAcquire(SyncScanLock, LW_EXCLUSIVE))
		{
			(void) ss_search(rel->rd_node, location, true);
			LWLockRelease(SyncScanLock);
		}
#ifdef TRACE_SYNCSCAN
		else if (trace_syncscan)
			elog(LOG,
				 "SYNC_SCAN: missed update for \"%s\" at %u",
				 RelationGetRelationName(rel), location);
#endif
