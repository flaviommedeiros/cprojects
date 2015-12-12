static struct insn opcode_e5[] = {
#ifdef CONFIG_64BIT
	{ "strag", 0x02, INSTR_SSE_RDRD },
	{ "mvhhi", 0x44, INSTR_SIL_RDI },
	{ "mvghi", 0x48, INSTR_SIL_RDI },
	{ "mvhi", 0x4c, INSTR_SIL_RDI },
	{ "chhsi", 0x54, INSTR_SIL_RDI },
	{ { 0, LONG_INSN_CLHHSI }, 0x55, INSTR_SIL_RDU },
	{ "cghsi", 0x58, INSTR_SIL_RDI },
	{ { 0, LONG_INSN_CLGHSI }, 0x59, INSTR_SIL_RDU },
	{ "chsi", 0x5c, INSTR_SIL_RDI },
	{ { 0, LONG_INSN_CLFHSI }, 0x5d, INSTR_SIL_RDU },
	{ { 0, LONG_INSN_TBEGIN }, 0x60, INSTR_SIL_RDU },
	{ { 0, LONG_INSN_TBEGINC }, 0x61, INSTR_SIL_RDU },
#endif
	{ "lasp", 0x00, INSTR_SSE_RDRD },
	{ "tprot", 0x01, INSTR_SSE_RDRD },
	{ "mvcsk", 0x0e, INSTR_SSE_RDRD },
	{ "mvcdk", 0x0f, INSTR_SSE_RDRD },
	{ "", 0, INSTR_INVALID }
};
