if (chip == &sun4u_irq_ack ||
	    chip == &sun4v_irq_ack ||
	    chip == &sun4v_virq_ack
#ifdef CONFIG_PCI_MSI
	    || chip == &sun4v_msi
#endif
	    )
		return;
