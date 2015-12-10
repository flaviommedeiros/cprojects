switch(ot) {
    case OT_BYTE:
        if (reg < 4 X86_64_DEF( || reg >= 8 || x86_64_hregs)) {
            tcg_gen_st8_tl(t0, cpu_env, offsetof(CPUState, regs[reg]) + REG_B_OFFSET);
        } else {
            tcg_gen_st8_tl(t0, cpu_env, offsetof(CPUState, regs[reg - 4]) + REG_H_OFFSET);
        }
        break;
    case OT_WORD:
        tcg_gen_st16_tl(t0, cpu_env, offsetof(CPUState, regs[reg]) + REG_W_OFFSET);
        break;
#ifdef TARGET_X86_64
    case OT_LONG:
        tcg_gen_st32_tl(t0, cpu_env, offsetof(CPUState, regs[reg]) + REG_L_OFFSET);
        /* high part of register set to zero */
        tcg_gen_movi_tl(cpu_tmp0, 0);
        tcg_gen_st32_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[reg]) + REG_LH_OFFSET);
        break;
    default:
    case OT_QUAD:
        tcg_gen_st_tl(t0, cpu_env, offsetof(CPUState, regs[reg]));
        break;
#else
    default:
    case OT_LONG:
        tcg_gen_st32_tl(t0, cpu_env, offsetof(CPUState, regs[reg]) + REG_L_OFFSET);
        break;
#endif
    }
