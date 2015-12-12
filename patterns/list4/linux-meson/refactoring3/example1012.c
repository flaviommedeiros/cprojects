switch (id) {
	case KVM_REG_PPC_HIOR:
		to_book3s(vcpu)->hior = set_reg_val(id, *val);
		to_book3s(vcpu)->hior_explicit = true;
		break;
#ifdef CONFIG_VSX
	case KVM_REG_PPC_VSR0 ... KVM_REG_PPC_VSR31: {
		long int i = id - KVM_REG_PPC_VSR0;

		if (!cpu_has_feature(CPU_FTR_VSX)) {
			r = -ENXIO;
			break;
		}
		vcpu->arch.fpr[i] = val->vsxval[0];
		vcpu->arch.vsr[i] = val->vsxval[1];
		break;
	}
#endif /* CONFIG_VSX */
	default:
		r = -EINVAL;
		break;
	}
