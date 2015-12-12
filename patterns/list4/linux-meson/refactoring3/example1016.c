switch (reg->id) {
		case KVM_REG_PPC_DAR:
			val = get_reg_val(reg->id, vcpu->arch.shared->dar);
			break;
		case KVM_REG_PPC_DSISR:
			val = get_reg_val(reg->id, vcpu->arch.shared->dsisr);
			break;
		case KVM_REG_PPC_FPR0 ... KVM_REG_PPC_FPR31:
			i = reg->id - KVM_REG_PPC_FPR0;
			val = get_reg_val(reg->id, vcpu->arch.fpr[i]);
			break;
		case KVM_REG_PPC_FPSCR:
			val = get_reg_val(reg->id, vcpu->arch.fpscr);
			break;
#ifdef CONFIG_ALTIVEC
		case KVM_REG_PPC_VR0 ... KVM_REG_PPC_VR31:
			if (!cpu_has_feature(CPU_FTR_ALTIVEC)) {
				r = -ENXIO;
				break;
			}
			val.vval = vcpu->arch.vr[reg->id - KVM_REG_PPC_VR0];
			break;
		case KVM_REG_PPC_VSCR:
			if (!cpu_has_feature(CPU_FTR_ALTIVEC)) {
				r = -ENXIO;
				break;
			}
			val = get_reg_val(reg->id, vcpu->arch.vscr.u[3]);
			break;
#endif /* CONFIG_ALTIVEC */
		case KVM_REG_PPC_DEBUG_INST: {
			u32 opcode = INS_TW;
			r = copy_to_user((u32 __user *)(long)reg->addr,
					 &opcode, sizeof(u32));
			break;
		}
#ifdef CONFIG_KVM_XICS
		case KVM_REG_PPC_ICP_STATE:
			if (!vcpu->arch.icp) {
				r = -ENXIO;
				break;
			}
			val = get_reg_val(reg->id, kvmppc_xics_get_icp(vcpu));
			break;
#endif /* CONFIG_KVM_XICS */
		default:
			r = -EINVAL;
			break;
		}
