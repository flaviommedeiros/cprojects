switch (data[0x1fc] & 15) {
		case 0: /* No partition / ADFS? */
			break;

#ifdef CONFIG_ACORN_PARTITION_RISCIX
		case PARTITION_RISCIX_SCSI:
			/* RISCiX - we don't know how to find the next one. */
			slot = riscix_partition(state, first_sector, slot,
						nr_sects);
			break;
#endif

		case PARTITION_LINUX:
			slot = linux_partition(state, first_sector, slot,
					       nr_sects);
			break;
		}
