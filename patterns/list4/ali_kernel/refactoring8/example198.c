static struct irq_cfg irq_cfgx[] = {
#else
static struct irq_cfg irq_cfgx[NR_IRQS] = {
#endif
	[0]  = { .vector = IRQ0_VECTOR,  },
	[1]  = { .vector = IRQ1_VECTOR,  },
	[2]  = { .vector = IRQ2_VECTOR,  },
	[3]  = { .vector = IRQ3_VECTOR,  },
	[4]  = { .vector = IRQ4_VECTOR,  },
	[5]  = { .vector = IRQ5_VECTOR,  },
	[6]  = { .vector = IRQ6_VECTOR,  },
	[7]  = { .vector = IRQ7_VECTOR,  },
	[8]  = { .vector = IRQ8_VECTOR,  },
	[9]  = { .vector = IRQ9_VECTOR,  },
	[10] = { .vector = IRQ10_VECTOR, },
	[11] = { .vector = IRQ11_VECTOR, },
	[12] = { .vector = IRQ12_VECTOR, },
	[13] = { .vector = IRQ13_VECTOR, },
	[14] = { .vector = IRQ14_VECTOR, },
	[15] = { .vector = IRQ15_VECTOR, },
};

void __init io_apic_disable_legacy(void)
{
	nr_legacy_irqs = 0;
	nr_irqs_gsi = 0;
}

int __init arch_early_irq_init(void)
{
	struct irq_cfg *cfg;
	struct irq_desc *desc;
	int count;
	int node;
	int i;

	cfg = irq_cfgx;
	count = ARRAY_SIZE(irq_cfgx);
	node= cpu_to_node(boot_cpu_id);

	for (i = 0; i < count; i++) {
		desc = irq_to_desc(i);
		desc->chip_data = &cfg[i];
		zalloc_cpumask_var_node(&cfg[i].domain, GFP_NOWAIT, node);
		zalloc_cpumask_var_node(&cfg[i].old_domain, GFP_NOWAIT, node);
		if (i < nr_legacy_irqs)
			cpumask_setall(cfg[i].domain);
	}

	return 0;
}

#ifdef CONFIG_SPARSE_IRQ
struct irq_cfg *irq_cfg(unsigned int irq)
{
	struct irq_cfg *cfg = NULL;
	struct irq_desc *desc;

	desc = irq_to_desc(irq);
	if (desc)
		cfg = desc->chip_data;

	return cfg;
}
