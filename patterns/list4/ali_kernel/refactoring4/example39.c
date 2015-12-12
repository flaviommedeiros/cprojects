#ifdef CONFIG_KGDB
if (kgdb_connected && arch_kgdb_ops.correct_hw_break)
		arch_kgdb_ops.correct_hw_break();
	else
#endif
		clear_all_debug_regs();
