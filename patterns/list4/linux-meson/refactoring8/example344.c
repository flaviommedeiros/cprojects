unsigned long timer_regs[NR_CPUS] =
{
	regi_timer0,
#ifdef CONFIG_SMP
	regi_timer2
#endif
};
