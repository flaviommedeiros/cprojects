switch (key) {
	case 'b': /* Bootable flag */
	{
		int fl = fdisk_is_label(cf->cxt, DOS) ? DOS_FLAG_ACTIVE :
			 fdisk_is_label(cf->cxt, SGI) ? SGI_FLAG_BOOT : 0;

		if (fl && fdisk_toggle_partition_flag(cf->cxt, n, fl))
			warn = _("Could not toggle the flag.");
		else if (fl)
			ref = 1;
		break;
	}
#ifdef KEY_DC
	case KEY_DC:
#endif
	case 'd': /* Delete */
		if (fdisk_delete_partition(cf->cxt, n) != 0)
			warn = _("Could not delete partition %zu.");
		else
			info = _("Partition %zu has been deleted.");
		ref = 1;
		break;
	case 'h': /* Help */
	case '?':
		ui_help();
		ref = 1;
		break;
	case 'n': /* New */
	{
		uint64_t start, size, dflt_size, secs;
		struct fdisk_partition *npa;	/* the new partition */
		int expsize = 0;		/* size specified explicitly in sectors */

		if (!fdisk_partition_is_freespace(pa) || !fdisk_partition_has_start(pa))
			return -EINVAL;

		/* free space range */
		start = fdisk_partition_get_start(pa);
		size = dflt_size = fdisk_partition_get_size(pa) * fdisk_get_sector_size(cf->cxt);

		if (ui_get_size(cf, _("Partition size: "), &size,
				fdisk_get_sector_size(cf->cxt),
				size, &expsize) == -CFDISK_ERR_ESC)
			break;

		secs = size / fdisk_get_sector_size(cf->cxt);

		npa = fdisk_new_partition();
		if (!npa)
			return -ENOMEM;

		if (dflt_size == size)	/* default is to fillin all free space */
			fdisk_partition_end_follow_default(npa, 1);
		else
			fdisk_partition_set_size(npa, secs);

		if (expsize)
			fdisk_partition_size_explicit(pa, 1);

		fdisk_partition_set_start(npa, start);
		fdisk_partition_partno_follow_default(npa, 1);
		/* add to disk label -- libfdisk will ask for missing details */
		rc = fdisk_add_partition(cf->cxt, npa, NULL);
		fdisk_unref_partition(npa);
		if (rc == 0)
			ref = 1;
		break;
	}
	case 'q': /* Quit */
		return 1;
	case 't': /* Type */
	{
		struct fdisk_parttype *t;

		if (fdisk_partition_is_freespace(pa))
			return -EINVAL;
		t = (struct fdisk_parttype *) fdisk_partition_get_type(pa);
		t = ui_get_parttype(cf, t);
		ref = 1;

		if (t && fdisk_set_partition_type(cf->cxt, n, t) == 0)
			info = _("Changed type of partition %zu.");
		else
			info = _("The type of partition %zu is unchanged.");
		break;
	}
	case 's': /* Sort */
		if (cf->wrong_order) {
			fdisk_reorder_partitions(cf->cxt);
			ref = 1;
		}
		break;
	case 'u': /* dUmp */
		ui_script_write(cf);
		break;
	case 'W': /* Write */
	{
		char buf[64] = { 0 };

		if (fdisk_is_readonly(cf->cxt)) {
			warn = _("Device is open in read-only mode.");
			break;
		}

		rc = ui_get_string(
			  _("Are you sure you want to write the partition "
			    "table to disk? "),
			  _("Type \"yes\" or \"no\", or press ESC to leave this dialog."),
			  buf, sizeof(buf));

		ref = 1;
		if (rc <= 0 || (strcasecmp(buf, "yes") != 0 &&
				strcasecmp(buf, _("yes")) != 0)) {
			info = _("Did not write partition table to disk.");
			break;
		}
		rc = fdisk_write_disklabel(cf->cxt);
		if (rc)
			warn = _("Failed to write disklabel.");
		else {
			fdisk_reread_partition_table(cf->cxt);
			info = _("The partition table has been altered.");
		}
		cf->nwrites++;
		break;
	}
	default:
		break;
	}
