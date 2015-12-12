#ifdef CONFIG_CHELSIO_T1_1G
if (!t1_is_asic(tp->adapter)) {
		/* FPGA */
		writel(0, tp->adapter->regs + FPGA_TP_ADDR_INTERRUPT_ENABLE);
		writel(tp_intr & ~FPGA_PCIX_INTERRUPT_TP,
		       tp->adapter->regs + A_PL_ENABLE);
	} else
#endif
	{
		writel(0, tp->adapter->regs + A_TP_INT_ENABLE);
		writel(tp_intr & ~F_PL_INTR_TP,
		       tp->adapter->regs + A_PL_ENABLE);
	}
