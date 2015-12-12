#ifdef CONFIG_OF
if (np)
			irq = irq_of_parse_and_map(np, i);
		else
#endif
			irq = combiner_lookup_irq(i);
