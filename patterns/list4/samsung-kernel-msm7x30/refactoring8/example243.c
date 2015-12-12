static struct insn opcode_01[] = {
#ifdef CONFIG_64BIT
	{ "sam64", 0x0e, INSTR_E },
	{ "pfpo", 0x0a, INSTR_E },
	{ "ptff", 0x04, INSTR_E },
#endif
	{ "pr", 0x01, INSTR_E },
	{ "upt", 0x02, INSTR_E },
	{ "sckpf", 0x07, INSTR_E },
	{ "tam", 0x0b, INSTR_E },
	{ "sam24", 0x0c, INSTR_E },
	{ "sam31", 0x0d, INSTR_E },
	{ "trap2", 0xff, INSTR_E },
	{ "", 0, INSTR_INVALID }
};
