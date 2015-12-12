switch (cmd) {
#ifndef CONFIG_8xx
	case 'd':	/* bd - hardware data breakpoint */
		mode = 7;
		cmd = inchar();
		if (cmd == 'r')
			mode = 5;
		else if (cmd == 'w')
			mode = 6;
		else
			termch = cmd;
		dabr.address = 0;
		dabr.enabled = 0;
		if (scanhex(&dabr.address)) {
			if (!is_kernel_addr(dabr.address)) {
				printf(badaddr);
				break;
			}
			dabr.address &= ~HW_BRK_TYPE_DABR;
			dabr.enabled = mode | BP_DABR;
		}
		break;

	case 'i':	/* bi - hardware instr breakpoint */
		if (!cpu_has_feature(CPU_FTR_ARCH_207S)) {
			printf("Hardware instruction breakpoint "
			       "not supported on this cpu\n");
			break;
		}
		if (iabr) {
			iabr->enabled &= ~BP_CIABR;
			iabr = NULL;
		}
		if (!scanhex(&a))
			break;
		if (!check_bp_loc(a))
			break;
		bp = new_breakpoint(a);
		if (bp != NULL) {
			bp->enabled |= BP_CIABR;
			iabr = bp;
		}
		break;
#endif

	case 'c':
		if (!scanhex(&a)) {
			/* clear all breakpoints */
			for (i = 0; i < NBPTS; ++i)
				bpts[i].enabled = 0;
			iabr = NULL;
			dabr.enabled = 0;
			printf("All breakpoints cleared\n");
			break;
		}

		if (a <= NBPTS && a >= 1) {
			/* assume a breakpoint number */
			bp = &bpts[a-1];	/* bp nums are 1 based */
		} else {
			/* assume a breakpoint address */
			bp = at_breakpoint(a);
			if (bp == NULL) {
				printf("No breakpoint at %lx\n", a);
				break;
			}
		}

		printf("Cleared breakpoint %lx (", BP_NUM(bp));
		xmon_print_symbol(bp->address, " ", ")\n");
		bp->enabled = 0;
		break;

	default:
		termch = cmd;
		cmd = skipbl();
		if (cmd == '?') {
			printf(breakpoint_help_string);
			break;
		}
		termch = cmd;
		if (!scanhex(&a)) {
			/* print all breakpoints */
			printf("   type            address\n");
			if (dabr.enabled) {
				printf("   data   "REG"  [", dabr.address);
				if (dabr.enabled & 1)
					printf("r");
				if (dabr.enabled & 2)
					printf("w");
				printf("]\n");
			}
			for (bp = bpts; bp < &bpts[NBPTS]; ++bp) {
				if (!bp->enabled)
					continue;
				printf("%2x %s   ", BP_NUM(bp),
				    (bp->enabled & BP_CIABR) ? "inst": "trap");
				xmon_print_symbol(bp->address, "  ", "\n");
			}
			break;
		}

		if (!check_bp_loc(a))
			break;
		bp = new_breakpoint(a);
		if (bp != NULL)
			bp->enabled |= BP_TRAP;
		break;
	}
