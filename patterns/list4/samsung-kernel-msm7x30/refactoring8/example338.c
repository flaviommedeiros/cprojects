static const union decode_item arm_cccc_0001_____1001_table[] = {
	/* Synchronization primitives					*/

#if __LINUX_ARM_ARCH__ < 6
	/* Deprecated on ARMv6 and may be UNDEFINED on v7		*/
	/* SMP/SWPB		cccc 0001 0x00 xxxx xxxx xxxx 1001 xxxx */
	DECODE_EMULATEX	(0x0fb000f0, 0x01000090, emulate_rd12rn16rm0_rwflags_nopc,
						 REGS(NOPC, NOPC, 0, 0, NOPC)),
#endif
	/* LDREX/STREX{,D,B,H}	cccc 0001 1xxx xxxx xxxx xxxx 1001 xxxx */
	/* And unallocated instructions...				*/
	DECODE_END
};
