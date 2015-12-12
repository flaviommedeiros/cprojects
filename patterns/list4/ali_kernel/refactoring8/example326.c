static volatile GPTIMER_group_regs *const group_regs[BFIN_TIMER_NUM_GROUP] =
{
	(GPTIMER_group_regs *)TIMER0_GROUP_REG,
#if (MAX_BLACKFIN_GPTIMERS > 8)
	(GPTIMER_group_regs *)TIMER8_GROUP_REG,
#endif
};
