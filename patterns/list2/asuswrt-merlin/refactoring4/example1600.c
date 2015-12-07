#ifdef DIAGNOSTIC
if (SH_TAILQ_FIRST(&hp->hash_bucket, __bh) == NULL)
#else
			if (atomic_read(&hp->hash_page_dirty) == 0)
#endif
				continue;
