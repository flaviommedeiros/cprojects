switch (id) {
	case KVM_REG_PPC_HIOR:
		*val = get_reg_val(id, to_book3s(vcpu)->hior);
		break;
#ifdef CONFIG_VSX
	case KVM_REG_PPC_VSR0 ... KVM_REG_PPC_VSR31: {
		long int i = id - KVM_REG_PPC_VSR0;

		if (!cpu_has_feature(CPU_FTR_VSX)) {
			r = -ENXIO;
			break;
		}
		val->vsxval[0] = vcpu->arch.fpr[i];
		val->vsxval[1] = vcpu->arch.vsr[i];
		break;
	}
#endif /* CONFIG_VSX */
	default:
		r = -EINVAL;
		break;
	}
