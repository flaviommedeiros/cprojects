static void __uasminit build_insn(u32 **buf, enum opcode opc, ...)
{
	struct insn *ip = NULL;
	unsigned int i;
	va_list ap;
	u32 op;

	for (i = 0; insn_table_MM[i].opcode != insn_invalid; i++)
		if (insn_table_MM[i].opcode == opc) {
			ip = &insn_table_MM[i];
			break;
		}

	if (!ip || (opc == insn_daddiu && r4k_daddiu_bug()))
		panic("Unsupported Micro-assembler instruction %d", opc);

	op = ip->match;
	va_start(ap, opc);
	if (ip->fields & RS) {
		if (opc == insn_mfc0 || opc == insn_mtc0)
			op |= build_rt(va_arg(ap, u32));
		else
			op |= build_rs(va_arg(ap, u32));
	}
	if (ip->fields & RT) {
		if (opc == insn_mfc0 || opc == insn_mtc0)
			op |= build_rs(va_arg(ap, u32));
		else
			op |= build_rt(va_arg(ap, u32));
	}
	if (ip->fields & RD)
		op |= build_rd(va_arg(ap, u32));
	if (ip->fields & RE)
		op |= build_re(va_arg(ap, u32));
	if (ip->fields & SIMM)
		op |= build_simm(va_arg(ap, s32));
	if (ip->fields & UIMM)
		op |= build_uimm(va_arg(ap, u32));
	if (ip->fields & BIMM)
		op |= build_bimm(va_arg(ap, s32));
	if (ip->fields & JIMM)
		op |= build_jimm(va_arg(ap, u32));
	if (ip->fields & FUNC)
		op |= build_func(va_arg(ap, u32));
	if (ip->fields & SET)
		op |= build_set(va_arg(ap, u32));
	if (ip->fields & SCIMM)
		op |= build_scimm(va_arg(ap, u32));
	va_end(ap);

#ifdef CONFIG_CPU_LITTLE_ENDIAN
	**buf = ((op & 0xffff) << 16) | (op >> 16);
#else
	**buf = op;
#endif
	(*buf)++;
}
