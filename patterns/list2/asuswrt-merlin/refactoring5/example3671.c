#ifdef CONFIG_PPC64
if (!is_32bit_task())
				childregs->gpr[13] = childregs->gpr[6];
			else
#endif
				childregs->gpr[2] = childregs->gpr[6];
