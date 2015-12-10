switch (op) {
    default: /* should never happen */ return 0;

    case CC_OP_EFLAGS: return compute_c_eflags();

    case CC_OP_MULB: return compute_c_mull();
    case CC_OP_MULW: return compute_c_mull();
    case CC_OP_MULL: return compute_c_mull();

    case CC_OP_ADDB: return compute_c_addb();
    case CC_OP_ADDW: return compute_c_addw();
    case CC_OP_ADDL: return compute_c_addl();

    case CC_OP_ADCB: return compute_c_adcb();
    case CC_OP_ADCW: return compute_c_adcw();
    case CC_OP_ADCL: return compute_c_adcl();

    case CC_OP_SUBB: return compute_c_subb();
    case CC_OP_SUBW: return compute_c_subw();
    case CC_OP_SUBL: return compute_c_subl();

    case CC_OP_SBBB: return compute_c_sbbb();
    case CC_OP_SBBW: return compute_c_sbbw();
    case CC_OP_SBBL: return compute_c_sbbl();

    case CC_OP_LOGICB: return compute_c_logicb();
    case CC_OP_LOGICW: return compute_c_logicw();
    case CC_OP_LOGICL: return compute_c_logicl();

    case CC_OP_INCB: return compute_c_incl();
    case CC_OP_INCW: return compute_c_incl();
    case CC_OP_INCL: return compute_c_incl();

    case CC_OP_DECB: return compute_c_incl();
    case CC_OP_DECW: return compute_c_incl();
    case CC_OP_DECL: return compute_c_incl();

    case CC_OP_SHLB: return compute_c_shlb();
    case CC_OP_SHLW: return compute_c_shlw();
    case CC_OP_SHLL: return compute_c_shll();

    case CC_OP_SARB: return compute_c_sarl();
    case CC_OP_SARW: return compute_c_sarl();
    case CC_OP_SARL: return compute_c_sarl();

#ifdef TARGET_X86_64
    case CC_OP_MULQ: return compute_c_mull();

    case CC_OP_ADDQ: return compute_c_addq();

    case CC_OP_ADCQ: return compute_c_adcq();

    case CC_OP_SUBQ: return compute_c_subq();

    case CC_OP_SBBQ: return compute_c_sbbq();

    case CC_OP_LOGICQ: return compute_c_logicq();

    case CC_OP_INCQ: return compute_c_incl();

    case CC_OP_DECQ: return compute_c_incl();

    case CC_OP_SHLQ: return compute_c_shlq();

    case CC_OP_SARQ: return compute_c_sarl();
#endif
    }
