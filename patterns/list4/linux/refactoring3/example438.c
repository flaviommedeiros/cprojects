switch(vp_mask) {
	case 0xfffffffffULL:
		kvmppc_mmu_pte_vflush_short(vcpu, guest_vp);
		break;
#ifdef CONFIG_PPC_BOOK3S_64
	case 0xffffffff0ULL:
		kvmppc_mmu_pte_vflush_64k(vcpu, guest_vp);
		break;
#endif
	case 0xffffff000ULL:
		kvmppc_mmu_pte_vflush_long(vcpu, guest_vp);
		break;
	default:
		WARN_ON(1);
		return;
	}
