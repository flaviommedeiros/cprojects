switch (id) {
	case KVM_REG_PPC_HIOR:
		/* Only allow this to be set to zero */
		if (set_reg_val(id, *val))
			r = -EINVAL;
		break;
	case KVM_REG_PPC_DABR:
		vcpu->arch.dabr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_DABRX:
		vcpu->arch.dabrx = set_reg_val(id, *val) & ~DABRX_HYP;
		break;
	case KVM_REG_PPC_DSCR:
		vcpu->arch.dscr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_PURR:
		vcpu->arch.purr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_SPURR:
		vcpu->arch.spurr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_AMR:
		vcpu->arch.amr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_UAMOR:
		vcpu->arch.uamor = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_MMCR0 ... KVM_REG_PPC_MMCRS:
		i = id - KVM_REG_PPC_MMCR0;
		vcpu->arch.mmcr[i] = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_PMC1 ... KVM_REG_PPC_PMC8:
		i = id - KVM_REG_PPC_PMC1;
		vcpu->arch.pmc[i] = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_SPMC1 ... KVM_REG_PPC_SPMC2:
		i = id - KVM_REG_PPC_SPMC1;
		vcpu->arch.spmc[i] = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_SIAR:
		vcpu->arch.siar = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_SDAR:
		vcpu->arch.sdar = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_SIER:
		vcpu->arch.sier = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_IAMR:
		vcpu->arch.iamr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_PSPB:
		vcpu->arch.pspb = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_DPDES:
		vcpu->arch.vcore->dpdes = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_DAWR:
		vcpu->arch.dawr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_DAWRX:
		vcpu->arch.dawrx = set_reg_val(id, *val) & ~DAWRX_HYP;
		break;
	case KVM_REG_PPC_CIABR:
		vcpu->arch.ciabr = set_reg_val(id, *val);
		/* Don't allow setting breakpoints in hypervisor code */
		if ((vcpu->arch.ciabr & CIABR_PRIV) == CIABR_PRIV_HYPER)
			vcpu->arch.ciabr &= ~CIABR_PRIV;	/* disable */
		break;
	case KVM_REG_PPC_CSIGR:
		vcpu->arch.csigr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TACR:
		vcpu->arch.tacr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TCSCR:
		vcpu->arch.tcscr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_PID:
		vcpu->arch.pid = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_ACOP:
		vcpu->arch.acop = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_WORT:
		vcpu->arch.wort = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_VPA_ADDR:
		addr = set_reg_val(id, *val);
		r = -EINVAL;
		if (!addr && (vcpu->arch.slb_shadow.next_gpa ||
			      vcpu->arch.dtl.next_gpa))
			break;
		r = set_vpa(vcpu, &vcpu->arch.vpa, addr, sizeof(struct lppaca));
		break;
	case KVM_REG_PPC_VPA_SLB:
		addr = val->vpaval.addr;
		len = val->vpaval.length;
		r = -EINVAL;
		if (addr && !vcpu->arch.vpa.next_gpa)
			break;
		r = set_vpa(vcpu, &vcpu->arch.slb_shadow, addr, len);
		break;
	case KVM_REG_PPC_VPA_DTL:
		addr = val->vpaval.addr;
		len = val->vpaval.length;
		r = -EINVAL;
		if (addr && (len < sizeof(struct dtl_entry) ||
			     !vcpu->arch.vpa.next_gpa))
			break;
		len -= len % sizeof(struct dtl_entry);
		r = set_vpa(vcpu, &vcpu->arch.dtl, addr, len);
		break;
	case KVM_REG_PPC_TB_OFFSET:
		/* round up to multiple of 2^24 */
		vcpu->arch.vcore->tb_offset =
			ALIGN(set_reg_val(id, *val), 1UL << 24);
		break;
	case KVM_REG_PPC_LPCR:
		kvmppc_set_lpcr(vcpu, set_reg_val(id, *val), true);
		break;
	case KVM_REG_PPC_LPCR_64:
		kvmppc_set_lpcr(vcpu, set_reg_val(id, *val), false);
		break;
	case KVM_REG_PPC_PPR:
		vcpu->arch.ppr = set_reg_val(id, *val);
		break;
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	case KVM_REG_PPC_TFHAR:
		vcpu->arch.tfhar = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TFIAR:
		vcpu->arch.tfiar = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TEXASR:
		vcpu->arch.texasr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_GPR0 ... KVM_REG_PPC_TM_GPR31:
		i = id - KVM_REG_PPC_TM_GPR0;
		vcpu->arch.gpr_tm[i] = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_VSR0 ... KVM_REG_PPC_TM_VSR63:
	{
		int j;
		i = id - KVM_REG_PPC_TM_VSR0;
		if (i < 32)
			for (j = 0; j < TS_FPRWIDTH; j++)
				vcpu->arch.fp_tm.fpr[i][j] = val->vsxval[j];
		else
			if (cpu_has_feature(CPU_FTR_ALTIVEC))
				vcpu->arch.vr_tm.vr[i-32] = val->vval;
			else
				r = -ENXIO;
		break;
	}
	case KVM_REG_PPC_TM_CR:
		vcpu->arch.cr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_LR:
		vcpu->arch.lr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_CTR:
		vcpu->arch.ctr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_FPSCR:
		vcpu->arch.fp_tm.fpscr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_AMR:
		vcpu->arch.amr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_PPR:
		vcpu->arch.ppr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_VRSAVE:
		vcpu->arch.vrsave_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_VSCR:
		if (cpu_has_feature(CPU_FTR_ALTIVEC))
			vcpu->arch.vr.vscr.u[3] = set_reg_val(id, *val);
		else
			r = - ENXIO;
		break;
	case KVM_REG_PPC_TM_DSCR:
		vcpu->arch.dscr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_TAR:
		vcpu->arch.tar_tm = set_reg_val(id, *val);
		break;
#endif
	case KVM_REG_PPC_ARCH_COMPAT:
		r = kvmppc_set_arch_compat(vcpu, set_reg_val(id, *val));
		break;
	default:
		r = -EINVAL;
		break;
	}
