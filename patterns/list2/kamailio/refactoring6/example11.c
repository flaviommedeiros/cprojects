if (
#ifdef DNS_WATCHDOG_SUPPORT
			/* remove expired elements only when the dns servers are up */
			servers_up &&
#endif
			/* automatically remove expired elements */
			((e->ent_flags & DNS_FLAG_PERMANENT) == 0) &&
			((s_ticks_t)(now-e->expire)>=0)
		) {
				_dns_hash_remove(e);
		}else if ((e->type==type) && (e->name_len==name->len) &&
			(strncasecmp(e->name, name->s, e->name_len)==0)){
			e->last_used=now;
#ifdef DNS_LU_LST
			/* add it at the end */
#ifdef DEBUG_LU_LST
			debug_lu_lst("_dns_hash_find: pre rm:", &e->last_used_lst);
#endif
			clist_rm(&e->last_used_lst, next, prev);
			clist_append(dns_last_used_lst, &e->last_used_lst, next, prev);
#ifdef DEBUG_LU_LST
			debug_lu_lst("_dns_hash_find: post append:", &e->last_used_lst);
#endif
#endif
			return e;
		}else if ((e->type==T_CNAME) &&
					!((e->rr_lst==0) || (e->ent_flags & DNS_FLAG_BAD_NAME)) &&
					(e->name_len==name->len) &&
					(strncasecmp(e->name, name->s, e->name_len)==0)){
			/*if CNAME matches and CNAME is entry is not a neg. cache entry
			  (could be produced by a specific CNAME lookup)*/
			e->last_used=now;
#ifdef DNS_LU_LST
			/* add it at the end */
#ifdef DEBUG_LU_LST
			debug_lu_lst("_dns_hash_find: cname: pre rm:", &e->last_used_lst);
#endif
			clist_rm(&e->last_used_lst, next, prev);
			clist_append(dns_last_used_lst, &e->last_used_lst, next, prev);
#ifdef DEBUG_LU_LST
			debug_lu_lst("_dns_hash_find: cname: post append:",
							&e->last_used_lst);
#endif
#endif
			ret=e; /* if this is an unfinished cname chain, we try to
					  return the last cname */
			/* this is a cname => retry using its value */
			if (cname_chain> MAX_CNAME_CHAIN){
				LM_ERR("cname chain too long or recursive (\"%.*s\")\n",
						name->len, name->s);
				ret=0; /* error*/
				*err=-1;
				break;
			}
			cname_chain++;
			cname.s=((struct cname_rdata*)e->rr_lst->rdata)->name;
			cname.len= ((struct cname_rdata*)e->rr_lst->rdata)->name_len;
			name=&cname;
			goto again;
		}
