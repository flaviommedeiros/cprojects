static struct cpu_info cpinfo[] = {
	{"ETRAX 1", 0, 0, 0},
	{"ETRAX 2", 1, 0, 0},
	{"ETRAX 3", 2, 0, 0},
	{"ETRAX 4", 3, 0, 0},
	{"Simulator", 7, 8, HAS_ETHERNET100 | HAS_SCSI | HAS_ATA},
	{"ETRAX 100", 8, 8, HAS_ETHERNET100 | HAS_SCSI | HAS_ATA | HAS_IRQ_BUG},
	{"ETRAX 100", 9, 8, HAS_ETHERNET100 | HAS_SCSI | HAS_ATA},

	{"ETRAX 100LX", 10, 8, HAS_ETHERNET100 | HAS_SCSI | HAS_ATA | HAS_USB
			     | HAS_MMU | HAS_MMU_BUG},

	{"ETRAX 100LX v2", 11, 8, HAS_ETHERNET100 | HAS_SCSI | HAS_ATA | HAS_USB
			        | HAS_MMU},
#ifdef CONFIG_ETRAXFS
	{"ETRAX FS", 32, 32, HAS_ETHERNET100 | HAS_ATA | HAS_MMU},
#else
	{"ARTPEC-3", 32, 32, HAS_ETHERNET100 | HAS_MMU},
#endif
	{"Unknown", 0, 0, 0}
};
