switch (sprn) {
	case SPRN_IBAT0U ... SPRN_IBAT3L:
	case SPRN_IBAT4U ... SPRN_IBAT7L:
	case SPRN_DBAT0U ... SPRN_DBAT3L:
	case SPRN_DBAT4U ... SPRN_DBAT7L:
	{
		struct kvmppc_bat *bat = kvmppc_find_bat(vcpu, sprn);

		if (sprn % 2)
			*spr_val = bat->raw >> 32;
		else
			*spr_val = bat->raw;

		break;
	}
	case SPRN_SDR1:
		if (!spr_allowed(vcpu, PRIV_HYPER))
			goto unprivileged;
		*spr_val = to_book3s(vcpu)->sdr1;
		break;
	case SPRN_DSISR:
		*spr_val = kvmppc_get_dsisr(vcpu);
		break;
	case SPRN_DAR:
		*spr_val = kvmppc_get_dar(vcpu);
		break;
	case SPRN_HIOR:
		*spr_val = to_book3s(vcpu)->hior;
		break;
	case SPRN_HID0:
		*spr_val = to_book3s(vcpu)->hid[0];
		break;
	case SPRN_HID1:
		*spr_val = to_book3s(vcpu)->hid[1];
		break;
	case SPRN_HID2:
	case SPRN_HID2_GEKKO:
		*spr_val = to_book3s(vcpu)->hid[2];
		break;
	case SPRN_HID4:
	case SPRN_HID4_GEKKO:
		*spr_val = to_book3s(vcpu)->hid[4];
		break;
	case SPRN_HID5:
		*spr_val = to_book3s(vcpu)->hid[5];
		break;
	case SPRN_CFAR:
	case SPRN_DSCR:
		*spr_val = 0;
		break;
	case SPRN_PURR:
		/*
		 * On exit we would have updated purr
		 */
		*spr_val = vcpu->arch.purr;
		break;
	case SPRN_SPURR:
		/*
		 * On exit we would have updated spurr
		 */
		*spr_val = vcpu->arch.spurr;
		break;
	case SPRN_VTB:
		*spr_val = vcpu->arch.vtb;
		break;
	case SPRN_IC:
		*spr_val = vcpu->arch.ic;
		break;
	case SPRN_GQR0:
	case SPRN_GQR1:
	case SPRN_GQR2:
	case SPRN_GQR3:
	case SPRN_GQR4:
	case SPRN_GQR5:
	case SPRN_GQR6:
	case SPRN_GQR7:
		*spr_val = to_book3s(vcpu)->gqr[sprn - SPRN_GQR0];
		break;
#ifdef CONFIG_PPC_BOOK3S_64
	case SPRN_FSCR:
		*spr_val = vcpu->arch.fscr;
		break;
	case SPRN_BESCR:
		*spr_val = vcpu->arch.bescr;
		break;
	case SPRN_EBBHR:
		*spr_val = vcpu->arch.ebbhr;
		break;
	case SPRN_EBBRR:
		*spr_val = vcpu->arch.ebbrr;
		break;
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	case SPRN_TFHAR:
		*spr_val = vcpu->arch.tfhar;
		break;
	case SPRN_TEXASR:
		*spr_val = vcpu->arch.texasr;
		break;
	case SPRN_TFIAR:
		*spr_val = vcpu->arch.tfiar;
		break;
#endif
#endif
	case SPRN_THRM1:
	case SPRN_THRM2:
	case SPRN_THRM3:
	case SPRN_CTRLF:
	case SPRN_CTRLT:
	case SPRN_L2CR:
	case SPRN_MMCR0_GEKKO:
	case SPRN_MMCR1_GEKKO:
	case SPRN_PMC1_GEKKO:
	case SPRN_PMC2_GEKKO:
	case SPRN_PMC3_GEKKO:
	case SPRN_PMC4_GEKKO:
	case SPRN_WPAR_GEKKO:
	case SPRN_MSSSR0:
	case SPRN_DABR:
#ifdef CONFIG_PPC_BOOK3S_64
	case SPRN_MMCRS:
	case SPRN_MMCRA:
	case SPRN_MMCR0:
	case SPRN_MMCR1:
	case SPRN_MMCR2:
	case SPRN_TIR:
#endif
		*spr_val = 0;
		break;
	default:
unprivileged:
		printk(KERN_INFO "KVM: invalid SPR read: %d\n", sprn);
#ifndef DEBUG_SPR
		emulated = EMULATE_FAIL;
#endif
		break;
	}
