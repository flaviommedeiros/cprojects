static struct bfin_gptimer_regs * const timer_regs[MAX_BLACKFIN_GPTIMERS] =
{
	(void *)TIMER0_CONFIG,
	(void *)TIMER1_CONFIG,
	(void *)TIMER2_CONFIG,
#if (MAX_BLACKFIN_GPTIMERS > 3)
	(void *)TIMER3_CONFIG,
	(void *)TIMER4_CONFIG,
	(void *)TIMER5_CONFIG,
	(void *)TIMER6_CONFIG,
	(void *)TIMER7_CONFIG,
# if (MAX_BLACKFIN_GPTIMERS > 8)
	(void *)TIMER8_CONFIG,
	(void *)TIMER9_CONFIG,
	(void *)TIMER10_CONFIG,
#  if (MAX_BLACKFIN_GPTIMERS > 11)
	(void *)TIMER11_CONFIG,
#  endif
# endif
#endif
};
