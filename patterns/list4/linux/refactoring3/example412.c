switch (id) {
	case KVM_REG_PPC_DEBUG_INST:
		*val = get_reg_val(id, KVMPPC_INST_SW_BREAKPOINT);
		break;
	case KVM_REG_PPC_HIOR:
		*val = get_reg_val(id, 0);
		break;
	case KVM_REG_PPC_DABR:
		*val = get_reg_val(id, vcpu->arch.dabr);
		break;
	case KVM_REG_PPC_DABRX:
		*val = get_reg_val(id, vcpu->arch.dabrx);
		break;
	case KVM_REG_PPC_DSCR:
		*val = get_reg_val(id, vcpu->arch.dscr);
		break;
	case KVM_REG_PPC_PURR:
		*val = get_reg_val(id, vcpu->arch.purr);
		break;
	case KVM_REG_PPC_SPURR:
		*val = get_reg_val(id, vcpu->arch.spurr);
		break;
	case KVM_REG_PPC_AMR:
		*val = get_reg_val(id, vcpu->arch.amr);
		break;
	case KVM_REG_PPC_UAMOR:
		*val = get_reg_val(id, vcpu->arch.uamor);
		break;
	case KVM_REG_PPC_MMCR0 ... KVM_REG_PPC_MMCRS:
		i = id - KVM_REG_PPC_MMCR0;
		*val = get_reg_val(id, vcpu->arch.mmcr[i]);
		break;
	case KVM_REG_PPC_PMC1 ... KVM_REG_PPC_PMC8:
		i = id - KVM_REG_PPC_PMC1;
		*val = get_reg_val(id, vcpu->arch.pmc[i]);
		break;
	case KVM_REG_PPC_SPMC1 ... KVM_REG_PPC_SPMC2:
		i = id - KVM_REG_PPC_SPMC1;
		*val = get_reg_val(id, vcpu->arch.spmc[i]);
		break;
	case KVM_REG_PPC_SIAR:
		*val = get_reg_val(id, vcpu->arch.siar);
		break;
	case KVM_REG_PPC_SDAR:
		*val = get_reg_val(id, vcpu->arch.sdar);
		break;
	case KVM_REG_PPC_SIER:
		*val = get_reg_val(id, vcpu->arch.sier);
		break;
	case KVM_REG_PPC_IAMR:
		*val = get_reg_val(id, vcpu->arch.iamr);
		break;
	case KVM_REG_PPC_PSPB:
		*val = get_reg_val(id, vcpu->arch.pspb);
		break;
	case KVM_REG_PPC_DPDES:
		*val = get_reg_val(id, vcpu->arch.vcore->dpdes);
		break;
	case KVM_REG_PPC_DAWR:
		*val = get_reg_val(id, vcpu->arch.dawr);
		break;
	case KVM_REG_PPC_DAWRX:
		*val = get_reg_val(id, vcpu->arch.dawrx);
		break;
	case KVM_REG_PPC_CIABR:
		*val = get_reg_val(id, vcpu->arch.ciabr);
		break;
	case KVM_REG_PPC_CSIGR:
		*val = get_reg_val(id, vcpu->arch.csigr);
		break;
	case KVM_REG_PPC_TACR:
		*val = get_reg_val(id, vcpu->arch.tacr);
		break;
	case KVM_REG_PPC_TCSCR:
		*val = get_reg_val(id, vcpu->arch.tcscr);
		break;
	case KVM_REG_PPC_PID:
		*val = get_reg_val(id, vcpu->arch.pid);
		break;
	case KVM_REG_PPC_ACOP:
		*val = get_reg_val(id, vcpu->arch.acop);
		break;
	case KVM_REG_PPC_WORT:
		*val = get_reg_val(id, vcpu->arch.wort);
		break;
	case KVM_REG_PPC_VPA_ADDR:
		spin_lock(&vcpu->arch.vpa_update_lock);
		*val = get_reg_val(id, vcpu->arch.vpa.next_gpa);
		spin_unlock(&vcpu->arch.vpa_update_lock);
		break;
	case KVM_REG_PPC_VPA_SLB:
		spin_lock(&vcpu->arch.vpa_update_lock);
		val->vpaval.addr = vcpu->arch.slb_shadow.next_gpa;
		val->vpaval.length = vcpu->arch.slb_shadow.len;
		spin_unlock(&vcpu->arch.vpa_update_lock);
		break;
	case KVM_REG_PPC_VPA_DTL:
		spin_lock(&vcpu->arch.vpa_update_lock);
		val->vpaval.addr = vcpu->arch.dtl.next_gpa;
		val->vpaval.length = vcpu->arch.dtl.len;
		spin_unlock(&vcpu->arch.vpa_update_lock);
		break;
	case KVM_REG_PPC_TB_OFFSET:
		*val = get_reg_val(id, vcpu->arch.vcore->tb_offset);
		break;
	case KVM_REG_PPC_LPCR:
	case KVM_REG_PPC_LPCR_64:
		*val = get_reg_val(id, vcpu->arch.vcore->lpcr);
		break;
	case KVM_REG_PPC_PPR:
		*val = get_reg_val(id, vcpu->arch.ppr);
		break;
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	case KVM_REG_PPC_TFHAR:
		*val = get_reg_val(id, vcpu->arch.tfhar);
		break;
	case KVM_REG_PPC_TFIAR:
		*val = get_reg_val(id, vcpu->arch.tfiar);
		break;
	case KVM_REG_PPC_TEXASR:
		*val = get_reg_val(id, vcpu->arch.texasr);
		break;
	case KVM_REG_PPC_TM_GPR0 ... KVM_REG_PPC_TM_GPR31:
		i = id - KVM_REG_PPC_TM_GPR0;
		*val = get_reg_val(id, vcpu->arch.gpr_tm[i]);
		break;
	case KVM_REG_PPC_TM_VSR0 ... KVM_REG_PPC_TM_VSR63:
	{
		int j;
		i = id - KVM_REG_PPC_TM_VSR0;
		if (i < 32)
			for (j = 0; j < TS_FPRWIDTH; j++)
				val->vsxval[j] = vcpu->arch.fp_tm.fpr[i][j];
		else {
			if (cpu_has_feature(CPU_FTR_ALTIVEC))
				val->vval = vcpu->arch.vr_tm.vr[i-32];
			else
				r = -ENXIO;
		}
		break;
	}
	case KVM_REG_PPC_TM_CR:
		*val = get_reg_val(id, vcpu->arch.cr_tm);
		break;
	case KVM_REG_PPC_TM_LR:
		*val = get_reg_val(id, vcpu->arch.lr_tm);
		break;
	case KVM_REG_PPC_TM_CTR:
		*val = get_reg_val(id, vcpu->arch.ctr_tm);
		break;
	case KVM_REG_PPC_TM_FPSCR:
		*val = get_reg_val(id, vcpu->arch.fp_tm.fpscr);
		break;
	case KVM_REG_PPC_TM_AMR:
		*val = get_reg_val(id, vcpu->arch.amr_tm);
		break;
	case KVM_REG_PPC_TM_PPR:
		*val = get_reg_val(id, vcpu->arch.ppr_tm);
		break;
	case KVM_REG_PPC_TM_VRSAVE:
		*val = get_reg_val(id, vcpu->arch.vrsave_tm);
		break;
	case KVM_REG_PPC_TM_VSCR:
		if (cpu_has_feature(CPU_FTR_ALTIVEC))
			*val = get_reg_val(id, vcpu->arch.vr_tm.vscr.u[3]);
		else
			r = -ENXIO;
		break;
	case KVM_REG_PPC_TM_DSCR:
		*val = get_reg_val(id, vcpu->arch.dscr_tm);
		break;
	case KVM_REG_PPC_TM_TAR:
		*val = get_reg_val(id, vcpu->arch.tar_tm);
		break;
#endif
	case KVM_REG_PPC_ARCH_COMPAT:
		*val = get_reg_val(id, vcpu->arch.vcore->arch_compat);
		break;
	default:
		r = -EINVAL;
		break;
	}
