switch (_inst) {
#ifdef CONFIG_BOOKE
	case KVM_INST_WRTEEI_0:
		kvm_patch_ins_wrteei_0(inst);
		break;

	case KVM_INST_WRTEEI_1:
		kvm_patch_ins_wrtee(inst, 0, 1);
		break;
#endif
	}
