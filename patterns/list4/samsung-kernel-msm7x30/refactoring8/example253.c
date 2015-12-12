static struct insn opcode_c8[] = {
#ifdef CONFIG_64BIT
	{ "mvcos", 0x00, INSTR_SSF_RRDRD },
	{ "ectg", 0x01, INSTR_SSF_RRDRD },
	{ "csst", 0x02, INSTR_SSF_RRDRD },
	{ "lpd", 0x04, INSTR_SSF_RRDRD2 },
	{ "lpdg ", 0x05, INSTR_SSF_RRDRD2 },
#endif
	{ "", 0, INSTR_INVALID }
};
