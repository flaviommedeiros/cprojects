switch (nvram_type_ids[read_type]) {
	case PSTORE_TYPE_DMESG:
		part = &oops_log_partition;
		*type = PSTORE_TYPE_DMESG;
		break;
	case PSTORE_TYPE_PPC_COMMON:
		sig = NVRAM_SIG_SYS;
		part = &common_partition;
		*type = PSTORE_TYPE_PPC_COMMON;
		*id = PSTORE_TYPE_PPC_COMMON;
		time->tv_sec = 0;
		time->tv_nsec = 0;
		break;
#ifdef CONFIG_PPC_PSERIES
	case PSTORE_TYPE_PPC_RTAS:
		part = &rtas_log_partition;
		*type = PSTORE_TYPE_PPC_RTAS;
		time->tv_sec = last_rtas_event;
		time->tv_nsec = 0;
		break;
	case PSTORE_TYPE_PPC_OF:
		sig = NVRAM_SIG_OF;
		part = &of_config_partition;
		*type = PSTORE_TYPE_PPC_OF;
		*id = PSTORE_TYPE_PPC_OF;
		time->tv_sec = 0;
		time->tv_nsec = 0;
		break;
#endif
#ifdef CONFIG_PPC_POWERNV
	case PSTORE_TYPE_PPC_OPAL:
		sig = NVRAM_SIG_FW;
		part = &skiboot_partition;
		*type = PSTORE_TYPE_PPC_OPAL;
		*id = PSTORE_TYPE_PPC_OPAL;
		time->tv_sec = 0;
		time->tv_nsec = 0;
		break;
#endif
	default:
		return 0;
	}
