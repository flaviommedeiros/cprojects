switch (get_xop(inst)) {

		case XOP_DCBTLS:
			emulated = kvmppc_e500_emul_dcbtls(vcpu);
			break;

#ifdef CONFIG_KVM_E500MC
		case XOP_MSGSND:
			emulated = kvmppc_e500_emul_msgsnd(vcpu, rb);
			break;

		case XOP_MSGCLR:
			emulated = kvmppc_e500_emul_msgclr(vcpu, rb);
			break;
#endif

		case XOP_TLBRE:
			emulated = kvmppc_e500_emul_tlbre(vcpu);
			break;

		case XOP_TLBWE:
			emulated = kvmppc_e500_emul_tlbwe(vcpu);
			break;

		case XOP_TLBSX:
			ea = kvmppc_get_ea_indexed(vcpu, ra, rb);
			emulated = kvmppc_e500_emul_tlbsx(vcpu, ea);
			break;

		case XOP_TLBILX: {
			int type = rt & 0x3;
			ea = kvmppc_get_ea_indexed(vcpu, ra, rb);
			emulated = kvmppc_e500_emul_tlbilx(vcpu, type, ea);
			break;
		}

		case XOP_TLBIVAX:
			ea = kvmppc_get_ea_indexed(vcpu, ra, rb);
			emulated = kvmppc_e500_emul_tlbivax(vcpu, ea);
			break;

		case XOP_MFTMR:
			emulated = kvmppc_e500_emul_mftmr(vcpu, inst, rt);
			break;

		case XOP_EHPRIV:
			emulated = kvmppc_e500_emul_ehpriv(run, vcpu, inst,
							   advance);
			break;

		default:
			emulated = EMULATE_FAIL;
		}
