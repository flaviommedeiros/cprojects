if (
#ifdef DNS_WATCHDOG_SUPPORT
			/* check the expiration time only when the servers are up */
			servers_up &&
#endif
			((e->ent_flags & DNS_FLAG_PERMANENT) == 0) &&
			((s_ticks_t)(now-rr->expire)>=0) /* expired rr */
		)
			continue;
