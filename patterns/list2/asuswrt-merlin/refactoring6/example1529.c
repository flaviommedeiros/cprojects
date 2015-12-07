if (
#ifdef CONFIG_X86_32
	    regno == GDB_SS || regno == GDB_FS || regno == GDB_GS ||
#endif
	    regno == GDB_SP || regno == GDB_ORIG_AX)
		return 0;
