static struct intc_prio_reg prio_registers[] __initdata = {
	{ 0xfffe0818, 0, 16, 4, /* IPR01 */ { IRQ0, IRQ1, IRQ2, IRQ3 } },
	{ 0xfffe081a, 0, 16, 4, /* IPR02 */ { IRQ4, IRQ5, IRQ6, IRQ7 } },
	{ 0xfffe0820, 0, 16, 4, /* IPR05 */ { PINT, 0, 0, 0 } },
	{ 0xfffe0c00, 0, 16, 4, /* IPR06 */ { DMAC0, DMAC1, DMAC2, DMAC3 } },
	{ 0xfffe0c02, 0, 16, 4, /* IPR07 */ { DMAC4, DMAC5, DMAC6, DMAC7 } },
	{ 0xfffe0c04, 0, 16, 4, /* IPR08 */ { USB, LCDC, CMT0, CMT1 } },
	{ 0xfffe0c06, 0, 16, 4, /* IPR09 */ { BSC, WDT, MTU0_ABCD, MTU0_VEF } },
	{ 0xfffe0c08, 0, 16, 4, /* IPR10 */ { MTU1_AB, MTU1_VU, MTU2_AB,
					      MTU2_VU } },
	{ 0xfffe0c0a, 0, 16, 4, /* IPR11 */ { MTU3_ABCD, MTU2_TCI3V, MTU4_ABCD,
					      MTU2_TCI4V } },
	{ 0xfffe0c0c, 0, 16, 4, /* IPR12 */ { ADC_ADI, IIC30, IIC31, IIC32 } },
	{ 0xfffe0c0e, 0, 16, 4, /* IPR13 */ { IIC33, SCIF0, SCIF1, SCIF2 } },
	{ 0xfffe0c10, 0, 16, 4, /* IPR14 */ { SCIF3, SSU0, SSU1, SSI0_SSII } },
#ifdef CONFIG_CPU_SUBTYPE_SH7203
	{ 0xfffe0c12, 0, 16, 4, /* IPR15 */ { SSI1_SSII, SSI2_SSII,
					      SSI3_SSII, 0 } },
	{ 0xfffe0c14, 0, 16, 4, /* IPR16 */ { FLCTL, 0, RTC, RCAN0 } },
	{ 0xfffe0c16, 0, 16, 4, /* IPR17 */ { RCAN1, 0, 0, 0 } },
#else
	{ 0xfffe0c12, 0, 16, 4, /* IPR15 */ { SSI1_SSII, SSI2_SSII,
					      SSI3_SSII, ROMDEC } },
	{ 0xfffe0c14, 0, 16, 4, /* IPR16 */ { FLCTL, SDHI, RTC, RCAN0 } },
	{ 0xfffe0c16, 0, 16, 4, /* IPR17 */ { RCAN1, SRC, IEBI, 0 } },
#endif
};
