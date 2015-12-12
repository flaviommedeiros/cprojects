switch (id) {
	case KVM_REG_PPC_HIOR:
		*val = get_reg_val(id, 0);
		break;
	case KVM_REG_PPC_DABR:
		*val = get_reg_val(id, vcpu->arch.dabr);
		break;
	case KVM_REG_PPC_DSCR:
		*val = get_reg_val(id, vcpu->arch.dscr);
		break;
	case KVM_REG_PPC_PURR:
		*val = get_reg_val(id, vcpu->arch.purr);
		break;
	case KVM_REG_PPC_SPURR:
		*val = get_reg_val(id, vcpu->arch.spurr);
		break;
	case KVM_REG_PPC_AMR:
		*val = get_reg_val(id, vcpu->arch.amr);
		break;
	case KVM_REG_PPC_UAMOR:
		*val = get_reg_val(id, vcpu->arch.uamor);
		break;
	case KVM_REG_PPC_MMCR0 ... KVM_REG_PPC_MMCRA:
		i = id - KVM_REG_PPC_MMCR0;
		*val = get_reg_val(id, vcpu->arch.mmcr[i]);
		break;
	case KVM_REG_PPC_PMC1 ... KVM_REG_PPC_PMC8:
		i = id - KVM_REG_PPC_PMC1;
		*val = get_reg_val(id, vcpu->arch.pmc[i]);
		break;
#ifdef CONFIG_VSX
	case KVM_REG_PPC_FPR0 ... KVM_REG_PPC_FPR31:
		if (cpu_has_feature(CPU_FTR_VSX)) {
			/* VSX => FP reg i is stored in arch.vsr[2*i] */
			long int i = id - KVM_REG_PPC_FPR0;
			*val = get_reg_val(id, vcpu->arch.vsr[2 * i]);
		} else {
			/* let generic code handle it */
			r = -EINVAL;
		}
		break;
	case KVM_REG_PPC_VSR0 ... KVM_REG_PPC_VSR31:
		if (cpu_has_feature(CPU_FTR_VSX)) {
			long int i = id - KVM_REG_PPC_VSR0;
			val->vsxval[0] = vcpu->arch.vsr[2 * i];
			val->vsxval[1] = vcpu->arch.vsr[2 * i + 1];
		} else {
			r = -ENXIO;
		}
		break;
#endif /* CONFIG_VSX */
	case KVM_REG_PPC_VPA_ADDR:
		spin_lock(&vcpu->arch.vpa_update_lock);
		*val = get_reg_val(id, vcpu->arch.vpa.next_gpa);
		spin_unlock(&vcpu->arch.vpa_update_lock);
		break;
	case KVM_REG_PPC_VPA_SLB:
		spin_lock(&vcpu->arch.vpa_update_lock);
		val->vpaval.addr = vcpu->arch.slb_shadow.next_gpa;
		val->vpaval.length = vcpu->arch.slb_shadow.len;
		spin_unlock(&vcpu->arch.vpa_update_lock);
		break;
	case KVM_REG_PPC_VPA_DTL:
		spin_lock(&vcpu->arch.vpa_update_lock);
		val->vpaval.addr = vcpu->arch.dtl.next_gpa;
		val->vpaval.length = vcpu->arch.dtl.len;
		spin_unlock(&vcpu->arch.vpa_update_lock);
		break;
	default:
		r = -EINVAL;
		break;
	}
