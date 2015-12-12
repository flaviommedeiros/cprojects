static struct insn opcode_a5[] = {
#ifdef CONFIG_64BIT
	{ "iihh", 0x00, INSTR_RI_RU },
	{ "iihl", 0x01, INSTR_RI_RU },
	{ "iilh", 0x02, INSTR_RI_RU },
	{ "iill", 0x03, INSTR_RI_RU },
	{ "nihh", 0x04, INSTR_RI_RU },
	{ "nihl", 0x05, INSTR_RI_RU },
	{ "nilh", 0x06, INSTR_RI_RU },
	{ "nill", 0x07, INSTR_RI_RU },
	{ "oihh", 0x08, INSTR_RI_RU },
	{ "oihl", 0x09, INSTR_RI_RU },
	{ "oilh", 0x0a, INSTR_RI_RU },
	{ "oill", 0x0b, INSTR_RI_RU },
	{ "llihh", 0x0c, INSTR_RI_RU },
	{ "llihl", 0x0d, INSTR_RI_RU },
	{ "llilh", 0x0e, INSTR_RI_RU },
	{ "llill", 0x0f, INSTR_RI_RU },
#endif
	{ "", 0, INSTR_INVALID }
};
