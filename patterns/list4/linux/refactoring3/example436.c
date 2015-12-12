switch (id) {
		case KVM_REG_PPC_DAR:
			kvmppc_set_dar(vcpu, set_reg_val(id, *val));
			break;
		case KVM_REG_PPC_DSISR:
			kvmppc_set_dsisr(vcpu, set_reg_val(id, *val));
			break;
		case KVM_REG_PPC_FPR0 ... KVM_REG_PPC_FPR31:
			i = id - KVM_REG_PPC_FPR0;
			VCPU_FPR(vcpu, i) = set_reg_val(id, *val);
			break;
		case KVM_REG_PPC_FPSCR:
			vcpu->arch.fp.fpscr = set_reg_val(id, *val);
			break;
#ifdef CONFIG_VSX
		case KVM_REG_PPC_VSR0 ... KVM_REG_PPC_VSR31:
			if (cpu_has_feature(CPU_FTR_VSX)) {
				i = id - KVM_REG_PPC_VSR0;
				vcpu->arch.fp.fpr[i][0] = val->vsxval[0];
				vcpu->arch.fp.fpr[i][1] = val->vsxval[1];
			} else {
				r = -ENXIO;
			}
			break;
#endif /* CONFIG_VSX */
#ifdef CONFIG_KVM_XICS
		case KVM_REG_PPC_ICP_STATE:
			if (!vcpu->arch.icp) {
				r = -ENXIO;
				break;
			}
			r = kvmppc_xics_set_icp(vcpu,
						set_reg_val(id, *val));
			break;
#endif /* CONFIG_KVM_XICS */
		case KVM_REG_PPC_FSCR:
			vcpu->arch.fscr = set_reg_val(id, *val);
			break;
		case KVM_REG_PPC_TAR:
			vcpu->arch.tar = set_reg_val(id, *val);
			break;
		case KVM_REG_PPC_EBBHR:
			vcpu->arch.ebbhr = set_reg_val(id, *val);
			break;
		case KVM_REG_PPC_EBBRR:
			vcpu->arch.ebbrr = set_reg_val(id, *val);
			break;
		case KVM_REG_PPC_BESCR:
			vcpu->arch.bescr = set_reg_val(id, *val);
			break;
		case KVM_REG_PPC_VTB:
			vcpu->arch.vtb = set_reg_val(id, *val);
			break;
		case KVM_REG_PPC_IC:
			vcpu->arch.ic = set_reg_val(id, *val);
			break;
		default:
			r = -EINVAL;
			break;
		}
