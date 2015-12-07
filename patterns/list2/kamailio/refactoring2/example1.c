#ifndef TIMER_DEBUG
if (delta > 2*(s_ticks_t)TIMER_MAX_DRIFT+1)
#endif
						LM_DBG("adjusting timer ticks (%lu) with %ld ms"
								" (%ld ticks)\n",
								(unsigned long)*ticks,
							(long)(delta*1000)/TIMER_TICKS_HZ, (long)delta);
