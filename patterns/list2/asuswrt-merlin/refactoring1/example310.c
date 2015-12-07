if (hw == mpic->spurious_vec)
		return -EINVAL;

#ifdef CONFIG_SMP
	else if (hw >= mpic->ipi_vecs[0]) {
		WARN_ON(!(mpic->flags & MPIC_PRIMARY));

		DBG("mpic: mapping as IPI\n");
		set_irq_chip_data(virq, mpic);
		set_irq_chip_and_handler(virq, &mpic->hc_ipi,
					 handle_percpu_irq);
		return 0;
	}
#endif
