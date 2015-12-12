switch (sprn) {
#ifndef CONFIG_KVM_BOOKE_HV
	case SPRN_PID:
		kvmppc_set_pid(vcpu, spr_val);
		break;
	case SPRN_PID1:
		if (spr_val != 0)
			return EMULATE_FAIL;
		vcpu_e500->pid[1] = spr_val;
		break;
	case SPRN_PID2:
		if (spr_val != 0)
			return EMULATE_FAIL;
		vcpu_e500->pid[2] = spr_val;
		break;
	case SPRN_MAS0:
		vcpu->arch.shared->mas0 = spr_val;
		break;
	case SPRN_MAS1:
		vcpu->arch.shared->mas1 = spr_val;
		break;
	case SPRN_MAS2:
		vcpu->arch.shared->mas2 = spr_val;
		break;
	case SPRN_MAS3:
		vcpu->arch.shared->mas7_3 &= ~(u64)0xffffffff;
		vcpu->arch.shared->mas7_3 |= spr_val;
		break;
	case SPRN_MAS4:
		vcpu->arch.shared->mas4 = spr_val;
		break;
	case SPRN_MAS6:
		vcpu->arch.shared->mas6 = spr_val;
		break;
	case SPRN_MAS7:
		vcpu->arch.shared->mas7_3 &= (u64)0xffffffff;
		vcpu->arch.shared->mas7_3 |= (u64)spr_val << 32;
		break;
#endif
	case SPRN_L1CSR0:
		vcpu_e500->l1csr0 = spr_val;
		vcpu_e500->l1csr0 &= ~(L1CSR0_DCFI | L1CSR0_CLFC);
		break;
	case SPRN_L1CSR1:
		vcpu_e500->l1csr1 = spr_val;
		break;
	case SPRN_HID0:
		vcpu_e500->hid0 = spr_val;
		break;
	case SPRN_HID1:
		vcpu_e500->hid1 = spr_val;
		break;

	case SPRN_MMUCSR0:
		emulated = kvmppc_e500_emul_mt_mmucsr0(vcpu_e500,
				spr_val);
		break;

	/* extra exceptions */
	case SPRN_IVOR32:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_UNAVAIL] = spr_val;
		break;
	case SPRN_IVOR33:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_DATA] = spr_val;
		break;
	case SPRN_IVOR34:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_ROUND] = spr_val;
		break;
	case SPRN_IVOR35:
		vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR] = spr_val;
		break;
#ifdef CONFIG_KVM_BOOKE_HV
	case SPRN_IVOR36:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL] = spr_val;
		break;
	case SPRN_IVOR37:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL_CRIT] = spr_val;
		break;
#endif
	default:
		emulated = kvmppc_booke_emulate_mtspr(vcpu, sprn, spr_val);
	}
