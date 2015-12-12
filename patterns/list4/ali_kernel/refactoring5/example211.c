#ifdef CONFIG_PPC64
if (!test_thread_flag(TIF_32BIT))
				childregs->gpr[13] = childregs->gpr[6];
			else
#endif
				childregs->gpr[2] = childregs->gpr[6];
