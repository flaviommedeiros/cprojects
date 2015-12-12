static struct hardwall_type hardwall_types[] = {
	{  /* user-space access to UDN */
		0,
		1,
		0,
		0,
		"udn",
		LIST_HEAD_INIT(hardwall_types[HARDWALL_UDN].list),
		__SPIN_LOCK_INITIALIZER(hardwall_types[HARDWALL_UDN].lock),
		NULL
	},
#ifndef __tilepro__
	{  /* user-space access to IDN */
		1,
		1,
		1,
		1,  /* disabled pending hypervisor support */
		"idn",
		LIST_HEAD_INIT(hardwall_types[HARDWALL_IDN].list),
		__SPIN_LOCK_INITIALIZER(hardwall_types[HARDWALL_IDN].lock),
		NULL
	},
	{  /* access to user-space IPI */
		2,
		0,
		0,
		0,
		"ipi",
		LIST_HEAD_INIT(hardwall_types[HARDWALL_IPI].list),
		__SPIN_LOCK_INITIALIZER(hardwall_types[HARDWALL_IPI].lock),
		NULL
	},
#endif
};
