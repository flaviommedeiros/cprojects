static struct insn opcode_e5[] = {
#ifdef CONFIG_64BIT
	{ "strag", 0x02, INSTR_SSE_RDRD },
#endif
	{ "lasp", 0x00, INSTR_SSE_RDRD },
	{ "tprot", 0x01, INSTR_SSE_RDRD },
	{ "mvcsk", 0x0e, INSTR_SSE_RDRD },
	{ "mvcdk", 0x0f, INSTR_SSE_RDRD },
	{ "", 0, INSTR_INVALID }
};
