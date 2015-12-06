#ifdef HAVE_CURSES
if (for_curses)
	{
		const char *cHrStatsOpt[] = {AS_BAD("DEAD "), AS_BAD("SICK "), "OFF  ", AS_BAD("REST "), AS_BAD(" ERR "), AS_BAD("WAIT "), cHr};
		const char *cHrStats;
		int cHrStatsI = (sizeof(cHrStatsOpt) / sizeof(*cHrStatsOpt)) - 1;
		bool all_dead = true, all_off = true, all_rdrv = true;
		struct cgpu_info *proc = cgpu;
		for (int i = 0; i < cgpu->procs; ++i, (proc = proc->next_proc))
		{
			switch (cHrStatsI) {
				default:
					if (proc->status == LIFE_WAIT)
						cHrStatsI = 5;
				case 5:
					if (proc->deven == DEV_RECOVER_ERR)
						cHrStatsI = 4;
				case 4:
					if (proc->deven == DEV_RECOVER)
						cHrStatsI = 3;
				case 3:
					if (proc->status == LIFE_SICK || proc->status == LIFE_DEAD || proc->status == LIFE_DEAD2)
					{
						cHrStatsI = 1;
						all_off = false;
					}
					else
					{
						if (likely(proc->deven == DEV_ENABLED))
							all_off = false;
						if (proc->deven != DEV_RECOVER_DRV)
							all_rdrv = false;
					}
				case 1:
					break;
			}
			if (likely(proc->status != LIFE_DEAD && proc->status != LIFE_DEAD2))
				all_dead = false;
			if (opt_show_procs)
				break;
		}
		if (unlikely(all_dead))
			cHrStatsI = 0;
		else
		if (unlikely(all_off))
			cHrStatsI = 2;
		cHrStats = cHrStatsOpt[cHrStatsI];
		if (cHrStatsI == 2 && all_rdrv)
			cHrStats = " RST ";
		
		format_statline(buf, bufsz,
		                cHrStats,
		                aHr, uHr,
		                accepted, rejected, stale,
		                wnotaccepted, waccepted,
		                hwerrs,
		                bad_diff1, bad_diff1 + good_diff1);
	}
	else
#endif
	{
		percentf4(rejpcbuf, sizeof(rejpcbuf), wnotaccepted, waccepted);
		percentf4(bnbuf, sizeof(bnbuf), bad_diff1, good_diff1);
		tailsprintf(buf, bufsz, "%ds:%s avg:%s u:%s | A:%d R:%d+%d(%s) HW:%d/%s",
			opt_log_interval,
			cHr, aHr, uHr,
			accepted,
			rejected,
			stale,
			rejpcbuf,
			hwerrs,
			bnbuf
		);
	}
