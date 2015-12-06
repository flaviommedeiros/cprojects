// NGREG 34
return strdup (
"=PC	pc\n"
"=BP	x29\n"
"=SP	sp\n"
"=A0	x0\n"
"=A1	x1\n"
"=A2	x2\n"
"=A3	x3\n"
#if 0
"=ZF	zf\n"
"=SF	nf\n"
"=OF	vf\n"
"=CF	cf\n"
"=SN	ox0\n"
#endif
"gpr	x0	.64	0	0\n"
"gpr	x1	.64	8	0\n"
"gpr	x2	.64	16	0\n"
"gpr	x3	.64	24	0\n"
"gpr	x4	.64	32	0\n"
"gpr	x5	.64	40	0\n"
"gpr	x6	.64	48	0\n"
"gpr	x7	.64	56	0\n"
"gpr	x8	.64	64	0\n"
"gpr	x9	.64	72	0\n"
"gpr	x10	.64	80	0\n"
"gpr	x11	.64	88	0\n"
"gpr	x12	.64	96	0\n"
"gpr	x13	.64	104	0\n"
"gpr	x14	.64	112	0\n"
"gpr	x15	.64	120	0\n"
"gpr	x16	.64	128	0\n"
"gpr	x17	.64	136	0\n"
"gpr	x18	.64	144	0\n"
"gpr	x19	.64	152	0\n"
"gpr	x20	.64	160	0\n"
"gpr	x21	.64	168	0\n"
"gpr	x22	.64	176	0\n"
"gpr	x23	.64	184	0\n"
"gpr	x24	.64	192	0\n"
"gpr	x25	.64	200	0\n"
"gpr	x26	.64	208	0\n"
"gpr	x27	.64	216	0\n"
"gpr	x28	.64	224	0\n"
"gpr	x29	.64	232	0\n"
"gpr	x30	.64	240	0\n"
"gpr	sp	.64	248	0\n"
"gpr	pc	.64	256	0\n"
"gpr	pstate	.64	264	0\n"
// extra linux regs in struct
//"gpr	ox0	.64	272	0\n"
//"gpr	sysno	.64	280	0\n"

// probably wrong
#if 0
"gpr	nf	.1	.256	0	sign\n" // msb bit of last op
"gpr	zf	.1	.257	0	zero\n" // set if last op is 0
"gpr	cf	.1	.258	0	carry\n" // set if last op carries
"gpr	vf	.1	.259	0	overflow\n" // set if overflows
#endif
);