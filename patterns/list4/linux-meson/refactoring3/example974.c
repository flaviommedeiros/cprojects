switch (inst_no_rt) {
	/* Loads */
	case KVM_INST_MFMSR:
		kvm_patch_ins_ld(inst, magic_var(msr), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_SPRG0):
		kvm_patch_ins_ld(inst, magic_var(sprg0), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_SPRG1):
		kvm_patch_ins_ld(inst, magic_var(sprg1), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_SPRG2):
		kvm_patch_ins_ld(inst, magic_var(sprg2), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_SPRG3):
		kvm_patch_ins_ld(inst, magic_var(sprg3), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_SRR0):
		kvm_patch_ins_ld(inst, magic_var(srr0), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_SRR1):
		kvm_patch_ins_ld(inst, magic_var(srr1), inst_rt);
		break;
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPR(SPRN_DEAR):
#else
	case KVM_INST_MFSPR(SPRN_DAR):
#endif
		kvm_patch_ins_ld(inst, magic_var(dar), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_DSISR):
		kvm_patch_ins_lwz(inst, magic_var(dsisr), inst_rt);
		break;

#ifdef CONFIG_PPC_BOOK3E_MMU
	case KVM_INST_MFSPR(SPRN_MAS0):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas0), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_MAS1):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas1), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_MAS2):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(mas2), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_MAS3):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas7_3) + 4, inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_MAS4):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas4), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_MAS6):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas6), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_MAS7):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas7_3), inst_rt);
		break;
#endif /* CONFIG_PPC_BOOK3E_MMU */

	case KVM_INST_MFSPR(SPRN_SPRG4):
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPR(SPRN_SPRG4R):
#endif
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(sprg4), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_SPRG5):
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPR(SPRN_SPRG5R):
#endif
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(sprg5), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_SPRG6):
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPR(SPRN_SPRG6R):
#endif
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(sprg6), inst_rt);
		break;
	case KVM_INST_MFSPR(SPRN_SPRG7):
#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPR(SPRN_SPRG7R):
#endif
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(sprg7), inst_rt);
		break;

#ifdef CONFIG_BOOKE
	case KVM_INST_MFSPR(SPRN_ESR):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(esr), inst_rt);
		break;
#endif

	case KVM_INST_MFSPR(SPRN_PIR):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(pir), inst_rt);
		break;


	/* Stores */
	case KVM_INST_MTSPR(SPRN_SPRG0):
		kvm_patch_ins_std(inst, magic_var(sprg0), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_SPRG1):
		kvm_patch_ins_std(inst, magic_var(sprg1), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_SPRG2):
		kvm_patch_ins_std(inst, magic_var(sprg2), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_SPRG3):
		kvm_patch_ins_std(inst, magic_var(sprg3), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_SRR0):
		kvm_patch_ins_std(inst, magic_var(srr0), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_SRR1):
		kvm_patch_ins_std(inst, magic_var(srr1), inst_rt);
		break;
#ifdef CONFIG_BOOKE
	case KVM_INST_MTSPR(SPRN_DEAR):
#else
	case KVM_INST_MTSPR(SPRN_DAR):
#endif
		kvm_patch_ins_std(inst, magic_var(dar), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_DSISR):
		kvm_patch_ins_stw(inst, magic_var(dsisr), inst_rt);
		break;
#ifdef CONFIG_PPC_BOOK3E_MMU
	case KVM_INST_MTSPR(SPRN_MAS0):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas0), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_MAS1):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas1), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_MAS2):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(mas2), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_MAS3):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas7_3) + 4, inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_MAS4):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas4), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_MAS6):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas6), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_MAS7):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas7_3), inst_rt);
		break;
#endif /* CONFIG_PPC_BOOK3E_MMU */

	case KVM_INST_MTSPR(SPRN_SPRG4):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(sprg4), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_SPRG5):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(sprg5), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_SPRG6):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(sprg6), inst_rt);
		break;
	case KVM_INST_MTSPR(SPRN_SPRG7):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(sprg7), inst_rt);
		break;

#ifdef CONFIG_BOOKE
	case KVM_INST_MTSPR(SPRN_ESR):
		if (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(esr), inst_rt);
		break;
#endif

	/* Nops */
	case KVM_INST_TLBSYNC:
		kvm_patch_ins_nop(inst);
		break;

	/* Rewrites */
	case KVM_INST_MTMSRD_L1:
		kvm_patch_ins_mtmsrd(inst, inst_rt);
		break;
	case KVM_INST_MTMSR:
	case KVM_INST_MTMSRD_L0:
		kvm_patch_ins_mtmsr(inst, inst_rt);
		break;
#ifdef CONFIG_BOOKE
	case KVM_INST_WRTEE:
		kvm_patch_ins_wrtee(inst, inst_rt, 0);
		break;
#endif
	}
