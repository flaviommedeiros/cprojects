static struct insn opcode_c2[] = {
#ifdef CONFIG_64BIT
	{ "slgfi", 0x04, INSTR_RIL_RU },
	{ "slfi", 0x05, INSTR_RIL_RU },
	{ "agfi", 0x08, INSTR_RIL_RI },
	{ "afi", 0x09, INSTR_RIL_RI },
	{ "algfi", 0x0a, INSTR_RIL_RU },
	{ "alfi", 0x0b, INSTR_RIL_RU },
	{ "cgfi", 0x0c, INSTR_RIL_RI },
	{ "cfi", 0x0d, INSTR_RIL_RI },
	{ "clgfi", 0x0e, INSTR_RIL_RU },
	{ "clfi", 0x0f, INSTR_RIL_RU },
	{ "msfi", 0x01, INSTR_RIL_RI },
	{ "msgfi", 0x00, INSTR_RIL_RI },
#endif
	{ "", 0, INSTR_INVALID }
};
