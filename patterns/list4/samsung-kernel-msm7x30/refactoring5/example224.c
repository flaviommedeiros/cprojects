#ifdef CONFIG_PPC_BOOK3S_64
if ((pvr >= 0x330000) && (pvr < 0x70330000)) {
		kvmppc_mmu_book3s_64_init(vcpu);
		if (!to_book3s(vcpu)->hior_explicit)
			to_book3s(vcpu)->hior = 0xfff00000;
		to_book3s(vcpu)->msr_mask = 0xffffffffffffffffULL;
		vcpu->arch.cpu_type = KVM_CPU_3S_64;
	} else
#endif
	{
		kvmppc_mmu_book3s_32_init(vcpu);
		if (!to_book3s(vcpu)->hior_explicit)
			to_book3s(vcpu)->hior = 0;
		to_book3s(vcpu)->msr_mask = 0xffffffffULL;
		vcpu->arch.cpu_type = KVM_CPU_3S_32;
	}
