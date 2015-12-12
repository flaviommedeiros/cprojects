if (mpic->protected && test_bit(hw, mpic->protected))
		return -EINVAL;

#ifdef CONFIG_SMP
	else if (hw >= mpic->ipi_vecs[0]) {
		WARN_ON(mpic->flags & MPIC_SECONDARY);

		DBG("mpic: mapping as IPI\n");
		irq_set_chip_data(virq, mpic);
		irq_set_chip_and_handler(virq, &mpic->hc_ipi,
					 handle_percpu_irq);
		return 0;
	}
#endif
