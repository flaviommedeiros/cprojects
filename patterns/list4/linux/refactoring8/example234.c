static u32 ppc64_stub_insns[] = {
	0x3d620000,			/* addis   r11,r2, <high> */
	0x396b0000,			/* addi    r11,r11, <low> */
	/* Save current r2 value in magic place on the stack. */
	0xf8410000|R2_STACK_OFFSET,	/* std     r2,R2_STACK_OFFSET(r1) */
	0xe98b0020,			/* ld      r12,32(r11) */
#if !defined(_CALL_ELF) || _CALL_ELF != 2
	/* Set up new r2 from function descriptor */
	0xe84b0028,			/* ld      r2,40(r11) */
#endif
	0x7d8903a6,			/* mtctr   r12 */
	0x4e800420			/* bctr */
};
