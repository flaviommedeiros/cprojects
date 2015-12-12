struct benchmarks list[] = {
		{&benchmark_nop, 0, "nop"},
		/*
		 * benchmark_pushpop{1,3} will have the optimised
		 * instruction emulation, whilst benchmark_pushpop{2,4} will
		 * be the equivalent unoptimised instructions.
		 */
		{&benchmark_pushpop1, 0, "stmdb	sp!, {r3-r11,lr}"},
		{&benchmark_pushpop1, 4, "ldmia	sp!, {r3-r11,pc}"},
		{&benchmark_pushpop2, 0, "stmdb	sp!, {r0-r8,lr}"},
		{&benchmark_pushpop2, 4, "ldmia	sp!, {r0-r8,pc}"},
		{&benchmark_pushpop3, 0, "stmdb	sp!, {r4,lr}"},
		{&benchmark_pushpop3, 4, "ldmia	sp!, {r4,pc}"},
		{&benchmark_pushpop4, 0, "stmdb	sp!, {r0,lr}"},
		{&benchmark_pushpop4, 4, "ldmia	sp!, {r0,pc}"},
#ifdef CONFIG_THUMB2_KERNEL
		{&benchmark_pushpop_thumb, 0, "push.n	{r0-r7,lr}"},
		{&benchmark_pushpop_thumb, 2, "pop.n	{r0-r7,pc}"},
#endif
		{0}
	};
