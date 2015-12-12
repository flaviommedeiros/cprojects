switch (msr_info->index) {
#ifdef CONFIG_X86_64
	case MSR_FS_BASE:
		msr_info->data = vmcs_readl(GUEST_FS_BASE);
		break;
	case MSR_GS_BASE:
		msr_info->data = vmcs_readl(GUEST_GS_BASE);
		break;
	case MSR_KERNEL_GS_BASE:
		vmx_load_host_state(to_vmx(vcpu));
		msr_info->data = to_vmx(vcpu)->msr_guest_kernel_gs_base;
		break;
#endif
	case MSR_EFER:
		return kvm_get_msr_common(vcpu, msr_info);
	case MSR_IA32_TSC:
		msr_info->data = guest_read_tsc(vcpu);
		break;
	case MSR_IA32_SYSENTER_CS:
		msr_info->data = vmcs_read32(GUEST_SYSENTER_CS);
		break;
	case MSR_IA32_SYSENTER_EIP:
		msr_info->data = vmcs_readl(GUEST_SYSENTER_EIP);
		break;
	case MSR_IA32_SYSENTER_ESP:
		msr_info->data = vmcs_readl(GUEST_SYSENTER_ESP);
		break;
	case MSR_IA32_BNDCFGS:
		if (!vmx_mpx_supported())
			return 1;
		msr_info->data = vmcs_read64(GUEST_BNDCFGS);
		break;
	case MSR_IA32_FEATURE_CONTROL:
		if (!nested_vmx_allowed(vcpu))
			return 1;
		msr_info->data = to_vmx(vcpu)->nested.msr_ia32_feature_control;
		break;
	case MSR_IA32_VMX_BASIC ... MSR_IA32_VMX_VMFUNC:
		if (!nested_vmx_allowed(vcpu))
			return 1;
		return vmx_get_vmx_msr(vcpu, msr_info->index, &msr_info->data);
	case MSR_IA32_XSS:
		if (!vmx_xsaves_supported())
			return 1;
		msr_info->data = vcpu->arch.ia32_xss;
		break;
	case MSR_TSC_AUX:
		if (!guest_cpuid_has_rdtscp(vcpu))
			return 1;
		/* Otherwise falls through */
	default:
		msr = find_msr_entry(to_vmx(vcpu), msr_info->index);
		if (msr) {
			msr_info->data = msr->data;
			break;
		}
		return kvm_get_msr_common(vcpu, msr_info);
	}
