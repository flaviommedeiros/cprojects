#ifdef USE_SLOW_TIMER
if (IS_FAST_TIMER(tl)){
#endif
		/* if fast timer */
			SET_RUNNING(tl);
			tl->next=tl->prev=0; /* debugging */
#ifdef TIMER_DEBUG
			tl->expires_no++;
#endif
			UNLOCK_TIMER_LIST(); /* acts also as write barrier */ 
				ret=tl->f(t, tl, tl->data);
				/* reset the configuration group handles */
				cfg_reset_all();
				if (ret==0){
					UNSET_RUNNING();
					LOCK_TIMER_LIST();
				}else{
					/* not one-shot, re-add it */
					LOCK_TIMER_LIST();
					if (ret!=(ticks_t)-1) /* ! periodic */
						tl->initial_timeout=ret;
					_timer_add(t, tl);
					UNSET_RUNNING();
				}
#ifdef USE_SLOW_TIMER
		}else{
			/* slow timer */
			SET_SLOW_LIST(tl);
			tl->slow_idx=slow_mark; /* current index */
			/* overflow check in timer_handler*/
			_timer_add_list(slow_l, tl);
			
		}
