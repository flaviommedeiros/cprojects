if (cmdstatp->have_sense &&
	    scode == RECOVERED_ERROR
#if ST_RECOVERED_WRITE_FATAL
	    && SRpnt->cmd[0] != WRITE_6
	    && SRpnt->cmd[0] != WRITE_FILEMARKS
#endif
	    ) {
		STp->recover_count++;
		STp->recover_reg++;

                DEB(
		if (debugging) {
			if (SRpnt->cmd[0] == READ_6)
				stp = "read";
			else if (SRpnt->cmd[0] == WRITE_6)
				stp = "write";
			else
				stp = "ioctl";
			printk(ST_DEB_MSG "%s: Recovered %s error (%d).\n", name, stp,
			       STp->recover_count);
		} ) /* end DEB */

		if (cmdstatp->flags == 0)
			return 0;
	}
