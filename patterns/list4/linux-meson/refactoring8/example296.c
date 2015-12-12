static struct insn opcode_aa[] = {
#ifdef CONFIG_64BIT
	{ { 0, LONG_INSN_RINEXT }, 0x00, INSTR_RI_RI },
	{ "rion", 0x01, INSTR_RI_RI },
	{ "tric", 0x02, INSTR_RI_RI },
	{ "rioff", 0x03, INSTR_RI_RI },
	{ { 0, LONG_INSN_RIEMIT }, 0x04, INSTR_RI_RI },
#endif
	{ "", 0, INSTR_INVALID }
};
