static struct insn opcode_a7[] = {
#ifdef CONFIG_64BIT
	{ "tmhh", 0x02, INSTR_RI_RU },
	{ "tmhl", 0x03, INSTR_RI_RU },
	{ "brctg", 0x07, INSTR_RI_RP },
	{ "lghi", 0x09, INSTR_RI_RI },
	{ "aghi", 0x0b, INSTR_RI_RI },
	{ "mghi", 0x0d, INSTR_RI_RI },
	{ "cghi", 0x0f, INSTR_RI_RI },
#endif
	{ "tmlh", 0x00, INSTR_RI_RU },
	{ "tmll", 0x01, INSTR_RI_RU },
	{ "brc", 0x04, INSTR_RI_UP },
	{ "bras", 0x05, INSTR_RI_RP },
	{ "brct", 0x06, INSTR_RI_RP },
	{ "lhi", 0x08, INSTR_RI_RI },
	{ "ahi", 0x0a, INSTR_RI_RI },
	{ "mhi", 0x0c, INSTR_RI_RI },
	{ "chi", 0x0e, INSTR_RI_RI },
	{ "", 0, INSTR_INVALID }
};
