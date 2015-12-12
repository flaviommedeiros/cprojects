static Elf_Addr get_stub(struct module *me, unsigned long value, long addend,
	enum elf_stub_type stub_type, Elf_Addr loc0, unsigned int targetsec)
{
	struct stub_entry *stub;
	int __maybe_unused d;

	/* initialize stub_offset to point in front of the section */
	if (!me->arch.section[targetsec].stub_offset) {
		loc0 -= (me->arch.section[targetsec].stub_entries + 1) *
				sizeof(struct stub_entry);
		/* get correct alignment for the stubs */
		loc0 = ALIGN(loc0, sizeof(struct stub_entry));
		me->arch.section[targetsec].stub_offset = loc0;
	}

	/* get address of stub entry */
	stub = (void *) me->arch.section[targetsec].stub_offset;
	me->arch.section[targetsec].stub_offset += sizeof(struct stub_entry);

	/* do not write outside available stub area */
	BUG_ON(0 == me->arch.section[targetsec].stub_entries--);


#ifndef CONFIG_64BIT
/* for 32-bit the stub looks like this:
 * 	ldil L'XXX,%r1
 * 	be,n R'XXX(%sr4,%r1)
 */
	//value = *(unsigned long *)((value + addend) & ~3); /* why? */

	stub->insns[0] = 0x20200000;	/* ldil L'XXX,%r1	*/
	stub->insns[1] = 0xe0202002;	/* be,n R'XXX(%sr4,%r1)	*/

	stub->insns[0] |= reassemble_21(lrsel(value, addend));
	stub->insns[1] |= reassemble_17(rrsel(value, addend) / 4);

#else
/* for 64-bit we have three kinds of stubs:
 * for normal function calls:
 * 	ldd 0(%dp),%dp
 * 	ldd 10(%dp), %r1
 * 	bve (%r1)
 * 	ldd 18(%dp), %dp
 *
 * for millicode:
 * 	ldil 0, %r1
 * 	ldo 0(%r1), %r1
 * 	ldd 10(%r1), %r1
 * 	bve,n (%r1)
 *
 * for direct branches (jumps between different section of the
 * same module):
 *	ldil 0, %r1
 *	ldo 0(%r1), %r1
 *	bve,n (%r1)
 */
	switch (stub_type) {
	case ELF_STUB_GOT:
		d = get_got(me, value, addend);
		if (d <= 15) {
			/* Format 5 */
			stub->insns[0] = 0x0f6010db; /* ldd 0(%dp),%dp	*/
			stub->insns[0] |= low_sign_unext(d, 5) << 16;
		} else {
			/* Format 3 */
			stub->insns[0] = 0x537b0000; /* ldd 0(%dp),%dp	*/
			stub->insns[0] |= reassemble_16a(d);
		}
		stub->insns[1] = 0x53610020;	/* ldd 10(%dp),%r1	*/
		stub->insns[2] = 0xe820d000;	/* bve (%r1)		*/
		stub->insns[3] = 0x537b0030;	/* ldd 18(%dp),%dp	*/
		break;
	case ELF_STUB_MILLI:
		stub->insns[0] = 0x20200000;	/* ldil 0,%r1		*/
		stub->insns[1] = 0x34210000;	/* ldo 0(%r1), %r1	*/
		stub->insns[2] = 0x50210020;	/* ldd 10(%r1),%r1	*/
		stub->insns[3] = 0xe820d002;	/* bve,n (%r1)		*/

		stub->insns[0] |= reassemble_21(lrsel(value, addend));
		stub->insns[1] |= reassemble_14(rrsel(value, addend));
		break;
	case ELF_STUB_DIRECT:
		stub->insns[0] = 0x20200000;    /* ldil 0,%r1           */
		stub->insns[1] = 0x34210000;    /* ldo 0(%r1), %r1      */
		stub->insns[2] = 0xe820d002;    /* bve,n (%r1)          */

		stub->insns[0] |= reassemble_21(lrsel(value, addend));
		stub->insns[1] |= reassemble_14(rrsel(value, addend));
		break;
	}

#endif

	return (Elf_Addr)stub;
}
