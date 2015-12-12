static struct insn opcode_c0[] = {
#ifdef CONFIG_64BIT
	{ "lgfi", 0x01, INSTR_RIL_RI },
	{ "xihf", 0x06, INSTR_RIL_RU },
	{ "xilf", 0x07, INSTR_RIL_RU },
	{ "iihf", 0x08, INSTR_RIL_RU },
	{ "iilf", 0x09, INSTR_RIL_RU },
	{ "nihf", 0x0a, INSTR_RIL_RU },
	{ "nilf", 0x0b, INSTR_RIL_RU },
	{ "oihf", 0x0c, INSTR_RIL_RU },
	{ "oilf", 0x0d, INSTR_RIL_RU },
	{ "llihf", 0x0e, INSTR_RIL_RU },
	{ "llilf", 0x0f, INSTR_RIL_RU },
#endif
	{ "larl", 0x00, INSTR_RIL_RP },
	{ "brcl", 0x04, INSTR_RIL_UP },
	{ "brasl", 0x05, INSTR_RIL_RP },
	{ "", 0, INSTR_INVALID }
};
