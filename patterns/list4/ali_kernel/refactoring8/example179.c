static struct insn opcode_c8[] = {
#ifdef CONFIG_64BIT
	{ "mvcos", 0x00, INSTR_SSF_RRDRD },
#endif
	{ "", 0, INSTR_INVALID }
};
