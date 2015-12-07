#ifdef USE_SLOW_TIMER
if (IS_IN_TIMER_SLOW()){
			UNSET_RUNNING_SLOW();
	}else 
#endif
		LM_CRIT("timer_allow_del called outside a timer handle\n");
