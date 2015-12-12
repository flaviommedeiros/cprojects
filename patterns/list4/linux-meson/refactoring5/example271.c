#ifdef CONFIG_SMP
if (!r && (vcpu->mode == IN_GUEST_MODE))
		apic->send_IPI_mask(get_cpu_mask(vcpu->cpu),
				POSTED_INTR_VECTOR);
	else
#endif
		kvm_vcpu_kick(vcpu);
