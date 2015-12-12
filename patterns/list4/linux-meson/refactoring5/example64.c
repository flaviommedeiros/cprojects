#ifdef CONFIG_CISS_SCSI_TAPE
if (strncmp(ENGAGE_SCSI, buffer, sizeof ENGAGE_SCSI - 1) == 0) {
		struct seq_file *seq = file->private_data;
		ctlr_info_t *h = seq->private;

		err = cciss_engage_scsi(h);
		if (err == 0)
			err = length;
	} else
#endif /* CONFIG_CISS_SCSI_TAPE */
		err = -EINVAL;
