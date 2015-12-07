if ((
#ifdef DNS_WATCHDOG_SUPPORT
			/* check the expiration time only when the servers are up */
			servers_up &&
#endif
			((e->ent_flags & DNS_FLAG_PERMANENT) == 0) &&
			((s_ticks_t)(now-rr->expire)>=0) /* expired entry */) ||
				(srv_marked(tried, idx)) ) /* already tried */{
			r_sums[idx].r_sum=0; /* 0 sum, to skip over it */
			r_sums[idx].rr=0;    /* debug: mark it as unused */
			continue;
		}
