if ((status & FDC1772STAT_RECNF)
#ifdef TRACKBUFFER
	    /* RECNF is no error after a multiple read when the FDC
	     * searched for a non-existant sector!
	     */
	    && !(read_track &&
	       FDC1772_READ(FDC1772REG_SECTOR) > unit[SelectedDrive].disktype->spt)
#endif
	    ) {
		if (Probing) {
			if (unit[SelectedDrive].disktype > disk_type) {
				/* try another disk type */
				unit[SelectedDrive].disktype--;
				set_capacity(disks[SelectedDrive],
				    unit[SelectedDrive].disktype->blocks);
			} else
				Probing = 0;
		} else {
			/* record not found, but not probing. Maybe stretch wrong ? Restart probing */
			if (unit[SelectedDrive].autoprobe) {
				unit[SelectedDrive].disktype = disk_type + NUM_DISK_TYPES - 1;
				set_capacity(disks[SelectedDrive],
				    unit[SelectedDrive].disktype->blocks);
				Probing = 1;
			}
		}
		if (Probing) {
			setup_req_params(SelectedDrive);
#ifdef TRACKBUFFER
			BufferDrive = -1;
#endif
			do_fd_action(SelectedDrive);
			return;
		}
		printk("fd%d: sector %d not found (side %d, track %d)\n",
		       SelectedDrive, FDC1772_READ(FDC1772REG_SECTOR), ReqSide, ReqTrack);
		goto err_end;
	}
