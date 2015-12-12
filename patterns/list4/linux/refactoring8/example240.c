static unsigned int default_hcall_list[] = {
	H_ENTER,
	H_REMOVE,
	H_PROTECT,
	H_BULK_REMOVE,
	H_PUT_TCE,
	H_CEDE,
#ifdef CONFIG_KVM_XICS
	H_XIRR,
	H_CPPR,
	H_EOI,
	H_IPI,
	H_IPOLL,
	H_XIRR_X,
#endif
	0
};
