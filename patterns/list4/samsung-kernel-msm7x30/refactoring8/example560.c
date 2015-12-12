static struct bfin_gptimer_group_regs * const group_regs[BFIN_TIMER_NUM_GROUP] =
{
	(void *)TIMER0_GROUP_REG,
#if (MAX_BLACKFIN_GPTIMERS > 8)
	(void *)TIMER8_GROUP_REG,
#endif
};
