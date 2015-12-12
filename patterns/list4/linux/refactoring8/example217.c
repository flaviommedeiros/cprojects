static const struct hypervisor_x86 *vmmouse_supported_hypervisors[] = {
	&x86_hyper_vmware,
#ifdef CONFIG_KVM_GUEST
	&x86_hyper_kvm,
#endif
};
