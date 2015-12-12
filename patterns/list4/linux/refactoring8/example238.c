static struct rtas_handler rtas_handlers[] = {
#ifdef CONFIG_KVM_XICS
	{ .name = "ibm,set-xive", .handler = kvm_rtas_set_xive },
	{ .name = "ibm,get-xive", .handler = kvm_rtas_get_xive },
	{ .name = "ibm,int-off",  .handler = kvm_rtas_int_off },
	{ .name = "ibm,int-on",   .handler = kvm_rtas_int_on },
#endif
};
