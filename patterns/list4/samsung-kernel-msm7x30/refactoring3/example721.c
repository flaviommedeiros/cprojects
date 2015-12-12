switch (msr_index) {
	case MSR_EFER:
		ret = kvm_set_msr_common(vcpu, msr_index, data);
		break;
#ifdef CONFIG_X86_64
	case MSR_FS_BASE:
		vmx_segment_cache_clear(vmx);
		vmcs_writel(GUEST_FS_BASE, data);
		break;
	case MSR_GS_BASE:
		vmx_segment_cache_clear(vmx);
		vmcs_writel(GUEST_GS_BASE, data);
		break;
	case MSR_KERNEL_GS_BASE:
		vmx_load_host_state(vmx);
		vmx->msr_guest_kernel_gs_base = data;
		break;
#endif
	case MSR_IA32_SYSENTER_CS:
		vmcs_write32(GUEST_SYSENTER_CS, data);
		break;
	case MSR_IA32_SYSENTER_EIP:
		vmcs_writel(GUEST_SYSENTER_EIP, data);
		break;
	case MSR_IA32_SYSENTER_ESP:
		vmcs_writel(GUEST_SYSENTER_ESP, data);
		break;
	case MSR_IA32_TSC:
		kvm_write_tsc(vcpu, data);
		break;
	case MSR_IA32_CR_PAT:
		if (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PAT) {
			vmcs_write64(GUEST_IA32_PAT, data);
			vcpu->arch.pat = data;
			break;
		}
		ret = kvm_set_msr_common(vcpu, msr_index, data);
		break;
	case MSR_TSC_AUX:
		if (!vmx->rdtscp_enabled)
			return 1;
		/* Check reserved bit, higher 32 bits should be zero */
		if ((data >> 32) != 0)
			return 1;
		/* Otherwise falls through */
	default:
		if (vmx_set_vmx_msr(vcpu, msr_index, data))
			break;
		msr = find_msr_entry(vmx, msr_index);
		if (msr) {
			u64 old_msr_data = msr->data;
			msr->data = data;
			if (msr - vmx->guest_msrs < vmx->save_nmsrs) {
				preempt_disable();
				ret = kvm_set_shared_msr(msr->index, msr->data,
							 msr->mask);
				preempt_enable();
				if (ret)
					msr->data = old_msr_data;
			}
			break;
		}
		ret = kvm_set_msr_common(vcpu, msr_index, data);
	}
