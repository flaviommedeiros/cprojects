switch (ct_str[0]) {
    case 'A': case 'B': case 'C': case 'D':
        ct->ct |= TCG_CT_REG;
        tcg_regset_set_reg(ct->u.regs, 3 + ct_str[0] - 'A');
        break;
    case 'r':
        ct->ct |= TCG_CT_REG;
        tcg_regset_set32(ct->u.regs, 0, 0xffffffff);
        break;
#ifdef CONFIG_SOFTMMU
    case 'L':                   /* qemu_ld constraint */
        ct->ct |= TCG_CT_REG;
        tcg_regset_set32(ct->u.regs, 0, 0xffffffff);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R3);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R4);
        break;
    case 'K':                   /* qemu_st[8..32] constraint */
        ct->ct |= TCG_CT_REG;
        tcg_regset_set32(ct->u.regs, 0, 0xffffffff);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R3);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R4);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R5);
#if TARGET_LONG_BITS == 64
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R6);
#endif
        break;
    case 'M':                   /* qemu_st64 constraint */
        ct->ct |= TCG_CT_REG;
        tcg_regset_set32(ct->u.regs, 0, 0xffffffff);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R3);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R4);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R5);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R6);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R7);
        break;
#else
    case 'L':
    case 'K':
        ct->ct |= TCG_CT_REG;
        tcg_regset_set32(ct->u.regs, 0, 0xffffffff);
        break;
    case 'M':
        ct->ct |= TCG_CT_REG;
        tcg_regset_set32(ct->u.regs, 0, 0xffffffff);
        tcg_regset_reset_reg(ct->u.regs, TCG_REG_R3);
        break;
#endif
    default:
        return -1;
    }
