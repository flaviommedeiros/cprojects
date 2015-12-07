#ifdef CONFIG_BUG
if (opcode == BFIN_BUG_OPCODE)
		pr_cont("BUG");
	else
#endif
	if ((opcode & 0xffffff00) == ProgCtrl_opcode)
		decode_ProgCtrl_0(opcode);
	else if ((opcode & 0xfffff000) == BRCC_opcode)
		decode_BRCC_0(opcode);
	else if ((opcode & 0xfffff000) == 0x2000)
		pr_cont("JUMP.S");
	else if ((opcode & 0xfe000000) == CALLa_opcode)
		decode_CALLa_0(opcode);
	else if ((opcode & 0xff8000C0) == LoopSetup_opcode)
		decode_LoopSetup_0(opcode);
	else if ((opcode & 0xfffffc00) == DspLDST_opcode)
		decode_dspLDST_0(opcode);
	else if ((opcode & 0xfffff000) == LDST_opcode)
		decode_LDST_0(opcode);
	else if ((opcode & 0xffffe000) == LDSTii_opcode)
		decode_LDSTii_0(opcode);
	else if ((opcode & 0xfc000000) == LDSTidxI_opcode)
		decode_LDSTidxI_0(opcode);
	else if (opcode & 0xffff0000)
		pr_cont("0x%08x", opcode);
	else
		pr_cont("0x%04x", opcode);
