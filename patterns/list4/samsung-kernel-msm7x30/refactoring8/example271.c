static const int arg_offs_table[] = {
#ifdef CONFIG_X86_32
	[0] = offsetof(struct pt_regs, ax),
	[1] = offsetof(struct pt_regs, dx),
	[2] = offsetof(struct pt_regs, cx)
#else /* CONFIG_X86_64 */
	[0] = offsetof(struct pt_regs, di),
	[1] = offsetof(struct pt_regs, si),
	[2] = offsetof(struct pt_regs, dx),
	[3] = offsetof(struct pt_regs, cx),
	[4] = offsetof(struct pt_regs, r8),
	[5] = offsetof(struct pt_regs, r9)
#endif
};
