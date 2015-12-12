static unsigned long irq_regs[NR_CPUS] =
{
  regi_irq,
#ifdef CONFIG_SMP
  regi_irq2,
#endif
};
