static struct insn opcode_ec[] = {
#ifdef CONFIG_64BIT
	{ "brxhg", 0x44, INSTR_RIE_RRP },
	{ "brxlg", 0x45, INSTR_RIE_RRP },
#endif
	{ "", 0, INSTR_INVALID }
};
