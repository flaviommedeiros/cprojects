switch(size) {
    case 0:
        tcg_gen_st16_tl(cpu_A0, cpu_env, offsetof(CPUState, regs[reg]) + REG_W_OFFSET);
        break;
#ifdef TARGET_X86_64
    case 1:
        tcg_gen_st32_tl(cpu_A0, cpu_env, offsetof(CPUState, regs[reg]) + REG_L_OFFSET);
        /* high part of register set to zero */
        tcg_gen_movi_tl(cpu_tmp0, 0);
        tcg_gen_st32_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[reg]) + REG_LH_OFFSET);
        break;
    default:
    case 2:
        tcg_gen_st_tl(cpu_A0, cpu_env, offsetof(CPUState, regs[reg]));
        break;
#else
    default:
    case 1:
        tcg_gen_st32_tl(cpu_A0, cpu_env, offsetof(CPUState, regs[reg]) + REG_L_OFFSET);
        break;
#endif
    }
