#ifdef USE_USBUTILS
if (cgpu->usbinfo.nodev)
		cg_wprintw(statuswin, "ZOMBIE");
	else
#endif
	if (cgpu->status == LIFE_DEAD)
		cg_wprintw(statuswin, "DEAD  ");
	else if (cgpu->status == LIFE_SICK)
		cg_wprintw(statuswin, "SICK  ");
	else if (cgpu->deven == DEV_DISABLED)
		cg_wprintw(statuswin, "OFF   ");
	else if (cgpu->deven == DEV_RECOVER)
		cg_wprintw(statuswin, "REST  ");
	else if (opt_widescreen) {
		char displayed_hashes[16], displayed_rolling[16];
		uint64_t d64;

		d64 = (double)cgpu->total_mhashes / dev_runtime * 1000000ull;
		suffix_string(d64, displayed_hashes, sizeof(displayed_hashes), 4);
		d64 = (double)cgpu->rolling * 1000000ull;
		suffix_string(d64, displayed_rolling, sizeof(displayed_rolling), 4);
		adj_width(wu, &wuwidth);
		adj_fwidth(cgpu->diff_accepted, &dawidth);
		adj_fwidth(cgpu->diff_rejected, &drwidth);
		adj_width(cgpu->hw_errors, &hwwidth);
		cg_wprintw(statuswin, "%6s / %6sh/s WU:%*.1f/m "
				"A:%*.0f R:%*.0f HW:%*d",
				displayed_rolling,
				displayed_hashes, wuwidth + 2, wu,
				dawidth, cgpu->diff_accepted,
				drwidth, cgpu->diff_rejected,
				hwwidth, cgpu->hw_errors);
	} else if (!alt_status) {
		char displayed_hashes[16], displayed_rolling[16];
		uint64_t d64;

		d64 = (double)cgpu->total_mhashes / dev_runtime * 1000000ull;
		suffix_string(d64, displayed_hashes, sizeof(displayed_hashes), 4);
		d64 = (double)cgpu->rolling * 1000000ull;
		suffix_string(d64, displayed_rolling, sizeof(displayed_rolling), 4);
		adj_width(wu, &wuwidth);
		cg_wprintw(statuswin, "%6s / %6sh/s WU:%*.1f/m", displayed_rolling,
			   displayed_hashes, wuwidth + 2, wu);
	} else {
		adj_fwidth(cgpu->diff_accepted, &dawidth);
		adj_fwidth(cgpu->diff_rejected, &drwidth);
		adj_width(cgpu->hw_errors, &hwwidth);
		cg_wprintw(statuswin, "A:%*.0f R:%*.0f HW:%*d",
				dawidth, cgpu->diff_accepted,
				drwidth, cgpu->diff_rejected,
				hwwidth, cgpu->hw_errors);
	}
