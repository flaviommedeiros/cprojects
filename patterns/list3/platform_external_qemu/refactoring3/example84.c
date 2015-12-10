switch (op) {
    default: /* should never happen */ return 0;

    case CC_OP_EFLAGS: return compute_all_eflags();

    case CC_OP_MULB: return compute_all_mulb();
    case CC_OP_MULW: return compute_all_mulw();
    case CC_OP_MULL: return compute_all_mull();

    case CC_OP_ADDB: return compute_all_addb();
    case CC_OP_ADDW: return compute_all_addw();
    case CC_OP_ADDL: return compute_all_addl();

    case CC_OP_ADCB: return compute_all_adcb();
    case CC_OP_ADCW: return compute_all_adcw();
    case CC_OP_ADCL: return compute_all_adcl();

    case CC_OP_SUBB: return compute_all_subb();
    case CC_OP_SUBW: return compute_all_subw();
    case CC_OP_SUBL: return compute_all_subl();

    case CC_OP_SBBB: return compute_all_sbbb();
    case CC_OP_SBBW: return compute_all_sbbw();
    case CC_OP_SBBL: return compute_all_sbbl();

    case CC_OP_LOGICB: return compute_all_logicb();
    case CC_OP_LOGICW: return compute_all_logicw();
    case CC_OP_LOGICL: return compute_all_logicl();

    case CC_OP_INCB: return compute_all_incb();
    case CC_OP_INCW: return compute_all_incw();
    case CC_OP_INCL: return compute_all_incl();

    case CC_OP_DECB: return compute_all_decb();
    case CC_OP_DECW: return compute_all_decw();
    case CC_OP_DECL: return compute_all_decl();

    case CC_OP_SHLB: return compute_all_shlb();
    case CC_OP_SHLW: return compute_all_shlw();
    case CC_OP_SHLL: return compute_all_shll();

    case CC_OP_SARB: return compute_all_sarb();
    case CC_OP_SARW: return compute_all_sarw();
    case CC_OP_SARL: return compute_all_sarl();

#ifdef TARGET_X86_64
    case CC_OP_MULQ: return compute_all_mulq();

    case CC_OP_ADDQ: return compute_all_addq();

    case CC_OP_ADCQ: return compute_all_adcq();

    case CC_OP_SUBQ: return compute_all_subq();

    case CC_OP_SBBQ: return compute_all_sbbq();

    case CC_OP_LOGICQ: return compute_all_logicq();

    case CC_OP_INCQ: return compute_all_incq();

    case CC_OP_DECQ: return compute_all_decq();

    case CC_OP_SHLQ: return compute_all_shlq();

    case CC_OP_SARQ: return compute_all_sarq();
#endif
    }
