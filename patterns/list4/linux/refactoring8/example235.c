static u32 ppc64_stub_mask[] = {
	0xffff0000,
	0xffff0000,
	0xffffffff,
	0xffffffff,
#if !defined(_CALL_ELF) || _CALL_ELF != 2
	0xffffffff,
#endif
	0xffffffff,
	0xffffffff
};
