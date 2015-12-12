REG cpu_reg[] = {
	{ HRDATA (IAR, IAR, 32) },
	{ HRDATA (ACC, ACC, 32) },
	{ HRDATA (EXT, EXT, 32) },
	{ FLDATA (Oflow, V, 1) },
	{ FLDATA (Carry, C, 1) },
	{ HRDATA (CES, CES, 32) },
	{ HRDATA (ipl, ipl, 32), REG_RO },
	{ HRDATA (iplpending, iplpending, 32), REG_RO },
	{ HRDATA (wait_state, wait_state, 32)},
	{ HRDATA (DSW, cpu_dsw, 32), REG_RO },
	{ HRDATA (RUNMODE, RUNMODE, 32) },
	{ HRDATA (BREAK, ibkpt_addr, 32) },
	{ ORDATA (WRU, sim_int_char, 8) },
	{ FLDATA (IntRun, tbit, 1) },

	{ HRDATA (ILSW0, ILSW[0], 32), REG_RO },
	{ HRDATA (ILSW1, ILSW[1], 32), REG_RO },
	{ HRDATA (ILSW2, ILSW[2], 32), REG_RO },
	{ HRDATA (ILSW3, ILSW[3], 32), REG_RO },
	{ HRDATA (ILSW4, ILSW[4], 32), REG_RO },
	{ HRDATA (ILSW5, ILSW[5], 32), REG_RO },

#ifdef ENABLE_1800_SUPPORT
	{ HRDATA (IS_1800, is_1800, 32), REG_RO|REG_HIDDEN},		/* is_1800 flag is part of state, but hidden */
	{ HRDATA (XR1,     XR[0],   16), REG_RO|REG_HIDDEN},		/* index registers are unhidden if CPU set to 1800 mode */
	{ HRDATA (XR2,     XR[1],   16), REG_RO|REG_HIDDEN},
	{ HRDATA (XR3,     XR[2],   16), REG_RO|REG_HIDDEN},
#endif

	{ HRDATA (ARF, ARF, 32) },
	{ NULL}
};
