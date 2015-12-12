switch (sprn) {
#ifndef CONFIG_KVM_BOOKE_HV
	case SPRN_PID:
		*spr_val = vcpu_e500->pid[0];
		break;
	case SPRN_PID1:
		*spr_val = vcpu_e500->pid[1];
		break;
	case SPRN_PID2:
		*spr_val = vcpu_e500->pid[2];
		break;
	case SPRN_MAS0:
		*spr_val = vcpu->arch.shared->mas0;
		break;
	case SPRN_MAS1:
		*spr_val = vcpu->arch.shared->mas1;
		break;
	case SPRN_MAS2:
		*spr_val = vcpu->arch.shared->mas2;
		break;
	case SPRN_MAS3:
		*spr_val = (u32)vcpu->arch.shared->mas7_3;
		break;
	case SPRN_MAS4:
		*spr_val = vcpu->arch.shared->mas4;
		break;
	case SPRN_MAS6:
		*spr_val = vcpu->arch.shared->mas6;
		break;
	case SPRN_MAS7:
		*spr_val = vcpu->arch.shared->mas7_3 >> 32;
		break;
#endif
	case SPRN_DECAR:
		*spr_val = vcpu->arch.decar;
		break;
	case SPRN_TLB0CFG:
		*spr_val = vcpu->arch.tlbcfg[0];
		break;
	case SPRN_TLB1CFG:
		*spr_val = vcpu->arch.tlbcfg[1];
		break;
	case SPRN_TLB0PS:
		if (!has_feature(vcpu, VCPU_FTR_MMU_V2))
			return EMULATE_FAIL;
		*spr_val = vcpu->arch.tlbps[0];
		break;
	case SPRN_TLB1PS:
		if (!has_feature(vcpu, VCPU_FTR_MMU_V2))
			return EMULATE_FAIL;
		*spr_val = vcpu->arch.tlbps[1];
		break;
	case SPRN_L1CSR0:
		*spr_val = vcpu_e500->l1csr0;
		break;
	case SPRN_L1CSR1:
		*spr_val = vcpu_e500->l1csr1;
		break;
	case SPRN_HID0:
		*spr_val = vcpu_e500->hid0;
		break;
	case SPRN_HID1:
		*spr_val = vcpu_e500->hid1;
		break;
	case SPRN_SVR:
		*spr_val = vcpu_e500->svr;
		break;

	case SPRN_MMUCSR0:
		*spr_val = 0;
		break;

	case SPRN_MMUCFG:
		*spr_val = vcpu->arch.mmucfg;
		break;
	case SPRN_EPTCFG:
		if (!has_feature(vcpu, VCPU_FTR_MMU_V2))
			return EMULATE_FAIL;
		/*
		 * Legacy Linux guests access EPTCFG register even if the E.PT
		 * category is disabled in the VM. Give them a chance to live.
		 */
		*spr_val = vcpu->arch.eptcfg;
		break;

	case SPRN_PWRMGTCR0:
		*spr_val = vcpu->arch.pwrmgtcr0;
		break;

	/* extra exceptions */
#ifdef CONFIG_SPE_POSSIBLE
	case SPRN_IVOR32:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_UNAVAIL];
		break;
	case SPRN_IVOR33:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_DATA];
		break;
	case SPRN_IVOR34:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_ROUND];
		break;
#endif
#ifdef CONFIG_ALTIVEC
	case SPRN_IVOR32:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ALTIVEC_UNAVAIL];
		break;
	case SPRN_IVOR33:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ALTIVEC_ASSIST];
		break;
#endif
	case SPRN_IVOR35:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR];
		break;
#ifdef CONFIG_KVM_BOOKE_HV
	case SPRN_IVOR36:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL];
		break;
	case SPRN_IVOR37:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL_CRIT];
		break;
#endif
	default:
		emulated = kvmppc_booke_emulate_mfspr(vcpu, sprn, spr_val);
	}
