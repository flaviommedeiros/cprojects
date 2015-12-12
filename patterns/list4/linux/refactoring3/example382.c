switch (inst_no_rt & ~KVM_MASK_RB) {
#ifdef CONFIG_PPC_BOOK3S_32
	case KVM_INST_MTSRIN:
		if (features & KVM_MAGIC_FEAT_SR) {
			u32 inst_rb = _inst & KVM_MASK_RB;
			kvm_patch_ins_mtsrin(inst, inst_rt, inst_rb);
		}
		break;
#endif
	}
