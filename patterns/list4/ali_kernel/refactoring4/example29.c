#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
if ((retval = request_irq(net_dev->irq, rt2860_interrupt, IRQF_SHARED, net_dev->name ,net_dev)))
#else
		if ((retval = request_irq(net_dev->irq,rt2860_interrupt, SA_INTERRUPT, net_dev->name ,net_dev)))
#endif
		{
			printk("RT2860: request_irq  ERROR(%d)\n", retval);
		}
