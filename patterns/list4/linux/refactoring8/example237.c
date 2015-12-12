static unsigned int default_hcall_list[] = {
	H_REMOVE,
	H_ENTER,
	H_READ,
	H_PROTECT,
	H_BULK_REMOVE,
	H_GET_TCE,
	H_PUT_TCE,
	H_SET_DABR,
	H_SET_XDABR,
	H_CEDE,
	H_PROD,
	H_CONFER,
	H_REGISTER_VPA,
#ifdef CONFIG_KVM_XICS
	H_EOI,
	H_CPPR,
	H_IPI,
	H_IPOLL,
	H_XIRR,
	H_XIRR_X,
#endif
	0
};
