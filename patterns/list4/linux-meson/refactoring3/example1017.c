switch (reg->id) {
		case KVM_REG_PPC_DAR:
			vcpu->arch.shared->dar = set_reg_val(reg->id, val);
			break;
		case KVM_REG_PPC_DSISR:
			vcpu->arch.shared->dsisr = set_reg_val(reg->id, val);
			break;
		case KVM_REG_PPC_FPR0 ... KVM_REG_PPC_FPR31:
			i = reg->id - KVM_REG_PPC_FPR0;
			vcpu->arch.fpr[i] = set_reg_val(reg->id, val);
			break;
		case KVM_REG_PPC_FPSCR:
			vcpu->arch.fpscr = set_reg_val(reg->id, val);
			break;
#ifdef CONFIG_ALTIVEC
		case KVM_REG_PPC_VR0 ... KVM_REG_PPC_VR31:
			if (!cpu_has_feature(CPU_FTR_ALTIVEC)) {
				r = -ENXIO;
				break;
			}
			vcpu->arch.vr[reg->id - KVM_REG_PPC_VR0] = val.vval;
			break;
		case KVM_REG_PPC_VSCR:
			if (!cpu_has_feature(CPU_FTR_ALTIVEC)) {
				r = -ENXIO;
				break;
			}
			vcpu->arch.vscr.u[3] = set_reg_val(reg->id, val);
			break;
#endif /* CONFIG_ALTIVEC */
#ifdef CONFIG_KVM_XICS
		case KVM_REG_PPC_ICP_STATE:
			if (!vcpu->arch.icp) {
				r = -ENXIO;
				break;
			}
			r = kvmppc_xics_set_icp(vcpu,
						set_reg_val(reg->id, val));
			break;
#endif /* CONFIG_KVM_XICS */
		default:
			r = -EINVAL;
			break;
		}
