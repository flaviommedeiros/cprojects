static const struct cpuinfo_data arc_cpu_tbl[] = {
#ifdef CONFIG_ISA_ARCOMPACT
	{ {0x20, "ARC 600"      }, 0x2F},
	{ {0x30, "ARC 700"      }, 0x33},
	{ {0x34, "ARC 700 R4.10"}, 0x34},
	{ {0x35, "ARC 700 R4.11"}, 0x35},
#else
	{ {0x50, "ARC HS38 R2.0"}, 0x51},
	{ {0x52, "ARC HS38 R2.1"}, 0x52},
#endif
	{ {0x00, NULL		} }
};
