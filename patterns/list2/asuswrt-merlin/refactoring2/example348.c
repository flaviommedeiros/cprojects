#if ENABLE_FEATURE_TOPMEM
if (scan_mask != TOPMEM_MASK)
#endif
			{
				n = ntop;
				top = xrealloc_vector(top, 6, ntop++);
				top[n].pid = p->pid;
				top[n].ppid = p->ppid;
				top[n].vsz = p->vsz;
#if ENABLE_FEATURE_TOP_CPU_USAGE_PERCENTAGE
				top[n].ticks = p->stime + p->utime;
#endif
				top[n].uid = p->uid;
				strcpy(top[n].state, p->state);
				strcpy(top[n].comm, p->comm);
#if ENABLE_FEATURE_TOP_SMP_PROCESS
				top[n].last_seen_on_cpu = p->last_seen_on_cpu;
#endif
			}
#if ENABLE_FEATURE_TOPMEM
			else { /* TOPMEM */
				if (!(p->smaps.mapped_ro | p->smaps.mapped_rw))
					continue; /* kernel threads are ignored */
				n = ntop;
				/* No bug here - top and topmem are the same */
				top = xrealloc_vector(topmem, 6, ntop++);
				strcpy(topmem[n].comm, p->comm);
				topmem[n].pid      = p->pid;
				topmem[n].vsz      = p->smaps.mapped_rw + p->smaps.mapped_ro;
				topmem[n].vszrw    = p->smaps.mapped_rw;
				topmem[n].rss_sh   = p->smaps.shared_clean + p->smaps.shared_dirty;
				topmem[n].rss      = p->smaps.private_clean + p->smaps.private_dirty + topmem[n].rss_sh;
				topmem[n].dirty    = p->smaps.private_dirty + p->smaps.shared_dirty;
				topmem[n].dirty_sh = p->smaps.shared_dirty;
				topmem[n].stack    = p->smaps.stack;
			}
