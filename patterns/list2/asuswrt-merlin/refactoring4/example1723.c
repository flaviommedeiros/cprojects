#ifdef CONFIG_SMP
if ( (eth_int_cause1 & 0x20202) ||
		(eth_int_cause2 & 0x20202) )
#else
	if (eth_int_cause1 & 0x20202)
#endif
		titan_ge_free_tx_queue(titan_ge_eth);
