switch (id) {
		case KVM_REG_PPC_DAR:
			*val = get_reg_val(id, kvmppc_get_dar(vcpu));
			break;
		case KVM_REG_PPC_DSISR:
			*val = get_reg_val(id, kvmppc_get_dsisr(vcpu));
			break;
		case KVM_REG_PPC_FPR0 ... KVM_REG_PPC_FPR31:
			i = id - KVM_REG_PPC_FPR0;
			*val = get_reg_val(id, VCPU_FPR(vcpu, i));
			break;
		case KVM_REG_PPC_FPSCR:
			*val = get_reg_val(id, vcpu->arch.fp.fpscr);
			break;
#ifdef CONFIG_VSX
		case KVM_REG_PPC_VSR0 ... KVM_REG_PPC_VSR31:
			if (cpu_has_feature(CPU_FTR_VSX)) {
				i = id - KVM_REG_PPC_VSR0;
				val->vsxval[0] = vcpu->arch.fp.fpr[i][0];
				val->vsxval[1] = vcpu->arch.fp.fpr[i][1];
			} else {
				r = -ENXIO;
			}
			break;
#endif /* CONFIG_VSX */
		case KVM_REG_PPC_DEBUG_INST:
			*val = get_reg_val(id, INS_TW);
			break;
#ifdef CONFIG_KVM_XICS
		case KVM_REG_PPC_ICP_STATE:
			if (!vcpu->arch.icp) {
				r = -ENXIO;
				break;
			}
			*val = get_reg_val(id, kvmppc_xics_get_icp(vcpu));
			break;
#endif /* CONFIG_KVM_XICS */
		case KVM_REG_PPC_FSCR:
			*val = get_reg_val(id, vcpu->arch.fscr);
			break;
		case KVM_REG_PPC_TAR:
			*val = get_reg_val(id, vcpu->arch.tar);
			break;
		case KVM_REG_PPC_EBBHR:
			*val = get_reg_val(id, vcpu->arch.ebbhr);
			break;
		case KVM_REG_PPC_EBBRR:
			*val = get_reg_val(id, vcpu->arch.ebbrr);
			break;
		case KVM_REG_PPC_BESCR:
			*val = get_reg_val(id, vcpu->arch.bescr);
			break;
		case KVM_REG_PPC_VTB:
			*val = get_reg_val(id, vcpu->arch.vtb);
			break;
		case KVM_REG_PPC_IC:
			*val = get_reg_val(id, vcpu->arch.ic);
			break;
		default:
			r = -EINVAL;
			break;
		}
