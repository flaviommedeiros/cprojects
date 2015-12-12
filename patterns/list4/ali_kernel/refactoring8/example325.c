static volatile GPTIMER_timer_regs *const timer_regs[MAX_BLACKFIN_GPTIMERS] =
{
	(GPTIMER_timer_regs *)TIMER0_CONFIG,
	(GPTIMER_timer_regs *)TIMER1_CONFIG,
	(GPTIMER_timer_regs *)TIMER2_CONFIG,
#if (MAX_BLACKFIN_GPTIMERS > 3)
	(GPTIMER_timer_regs *)TIMER3_CONFIG,
	(GPTIMER_timer_regs *)TIMER4_CONFIG,
	(GPTIMER_timer_regs *)TIMER5_CONFIG,
	(GPTIMER_timer_regs *)TIMER6_CONFIG,
	(GPTIMER_timer_regs *)TIMER7_CONFIG,
# if (MAX_BLACKFIN_GPTIMERS > 8)
	(GPTIMER_timer_regs *)TIMER8_CONFIG,
	(GPTIMER_timer_regs *)TIMER9_CONFIG,
	(GPTIMER_timer_regs *)TIMER10_CONFIG,
#  if (MAX_BLACKFIN_GPTIMERS > 11)
	(GPTIMER_timer_regs *)TIMER11_CONFIG,
#  endif
# endif
#endif
};
