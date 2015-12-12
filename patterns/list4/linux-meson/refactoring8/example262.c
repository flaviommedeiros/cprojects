u8 DRXD_InitSC[] = {
	WR16(SC_COMM_EXEC__A, 0),
	WR16(SC_COMM_STATE__A, 0),

#ifdef COMPILE_FOR_QT
	WR16(SC_RA_RAM_BE_OPT_DELAY__A, 0x100),
#endif

	/* SC is not started, this is done in SetChannels() */
	END_OF_TABLE
};
