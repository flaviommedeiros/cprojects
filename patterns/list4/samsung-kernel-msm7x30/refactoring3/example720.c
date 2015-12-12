switch (msr_index) {
#ifdef CONFIG_X86_64
	case MSR_FS_BASE:
		data = vmcs_readl(GUEST_FS_BASE);
		break;
	case MSR_GS_BASE:
		data = vmcs_readl(GUEST_GS_BASE);
		break;
	case MSR_KERNEL_GS_BASE:
		vmx_load_host_state(to_vmx(vcpu));
		data = to_vmx(vcpu)->msr_guest_kernel_gs_base;
		break;
#endif
	case MSR_EFER:
		return kvm_get_msr_common(vcpu, msr_index, pdata);
	case MSR_IA32_TSC:
		data = guest_read_tsc();
		break;
	case MSR_IA32_SYSENTER_CS:
		data = vmcs_read32(GUEST_SYSENTER_CS);
		break;
	case MSR_IA32_SYSENTER_EIP:
		data = vmcs_readl(GUEST_SYSENTER_EIP);
		break;
	case MSR_IA32_SYSENTER_ESP:
		data = vmcs_readl(GUEST_SYSENTER_ESP);
		break;
	case MSR_TSC_AUX:
		if (!to_vmx(vcpu)->rdtscp_enabled)
			return 1;
		/* Otherwise falls through */
	default:
		if (vmx_get_vmx_msr(vcpu, msr_index, pdata))
			return 0;
		msr = find_msr_entry(to_vmx(vcpu), msr_index);
		if (msr) {
			data = msr->data;
			break;
		}
		return kvm_get_msr_common(vcpu, msr_index, pdata);
	}
