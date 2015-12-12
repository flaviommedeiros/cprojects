switch (id) {
#ifdef CONFIG_ACORN_PARTITION_RISCIX
		case PARTITION_RISCIX_SCSI:
		case PARTITION_RISCIX_MFM:
			slot = riscix_partition(state, start_sect, slot,
						nr_sects);
			break;
#endif

		case PARTITION_LINUX:
			slot = linux_partition(state, start_sect, slot,
					       nr_sects);
			break;
		}
