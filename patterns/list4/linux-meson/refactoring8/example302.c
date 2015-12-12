static struct insn opcode_c4[] = {
#ifdef CONFIG_64BIT
	{ "llhrl", 0x02, INSTR_RIL_RP },
	{ "lghrl", 0x04, INSTR_RIL_RP },
	{ "lhrl", 0x05, INSTR_RIL_RP },
	{ { 0, LONG_INSN_LLGHRL }, 0x06, INSTR_RIL_RP },
	{ "sthrl", 0x07, INSTR_RIL_RP },
	{ "lgrl", 0x08, INSTR_RIL_RP },
	{ "stgrl", 0x0b, INSTR_RIL_RP },
	{ "lgfrl", 0x0c, INSTR_RIL_RP },
	{ "lrl", 0x0d, INSTR_RIL_RP },
	{ { 0, LONG_INSN_LLGFRL }, 0x0e, INSTR_RIL_RP },
	{ "strl", 0x0f, INSTR_RIL_RP },
#endif
	{ "", 0, INSTR_INVALID }
};
