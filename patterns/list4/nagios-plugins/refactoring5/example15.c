#  ifdef _AIX
if (!allswaps) {
		fgets(input_buffer, MAX_INPUT_BUFFER - 1, child_process);	/* Ignore first line */
		sscanf (input_buffer, swap_format, &total_swap_mb, &used_swap_mb);
		free_swap_mb = total_swap_mb * (100 - used_swap_mb) /100;
		used_swap_mb = total_swap_mb - free_swap_mb;
		if (verbose >= 3)
			printf (_("total=%.0f, used=%.0f, free=%.0f\n"), total_swap_mb, used_swap_mb, free_swap_mb);
	} else {
#  endif
		while (fgets (input_buffer, MAX_INPUT_BUFFER - 1, child_process)) {
			sscanf (input_buffer, swap_format, &dsktotal_mb, &dskfree_mb);

			dsktotal_mb = dsktotal_mb / conv_factor;
			/* AIX lists percent used, so this converts to dskfree in MBs */
#  ifdef _AIX
			dskfree_mb = dsktotal_mb * (100 - dskfree_mb) / 100;
#  else
			dskfree_mb = dskfree_mb / conv_factor;
#  endif
			if (verbose >= 3)
				printf (_("total=%.0f, free=%.0f\n"), dsktotal_mb, dskfree_mb);

			dskused_mb = dsktotal_mb - dskfree_mb;
			total_swap_mb += dsktotal_mb;
			used_swap_mb += dskused_mb;
			free_swap_mb += dskfree_mb;
			if (allswaps) {
				percent = 100 * (((double) dskused_mb) / ((double) dsktotal_mb));
				result = max_state (result, check_swap (percent, dskfree_mb));
				if (verbose)
					xasprintf (&status, "%s [%.0f (%d%%)]", status, dskfree_mb, 100 - percent);
			}
		}
#  ifdef _AIX
	}
