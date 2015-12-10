switch(size) {
    case 0:
        tcg_gen_ld_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[reg]));
        tcg_gen_addi_tl(cpu_tmp0, cpu_tmp0, val);
        tcg_gen_st16_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[reg]) + REG_W_OFFSET);
        break;
    case 1:
        tcg_gen_ld_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[reg]));
        tcg_gen_addi_tl(cpu_tmp0, cpu_tmp0, val);
#ifdef TARGET_X86_64
        tcg_gen_andi_tl(cpu_tmp0, cpu_tmp0, 0xffffffff);
#endif
        tcg_gen_st_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[reg]));
        break;
#ifdef TARGET_X86_64
    case 2:
        tcg_gen_ld_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[reg]));
        tcg_gen_addi_tl(cpu_tmp0, cpu_tmp0, val);
        tcg_gen_st_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[reg]));
        break;
#endif
    }
