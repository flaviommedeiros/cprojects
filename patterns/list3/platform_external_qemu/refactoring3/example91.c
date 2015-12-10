switch(size) {
            case 0:
                tcg_gen_andi_tl(cpu_tmp0, cpu_cc_dst, 0x80);
                tcg_gen_brcondi_tl(inv ? TCG_COND_EQ : TCG_COND_NE, cpu_tmp0,
                                   0, l1);
                break;
            case 1:
                tcg_gen_andi_tl(cpu_tmp0, cpu_cc_dst, 0x8000);
                tcg_gen_brcondi_tl(inv ? TCG_COND_EQ : TCG_COND_NE, cpu_tmp0,
                                   0, l1);
                break;
#ifdef TARGET_X86_64
            case 2:
                tcg_gen_andi_tl(cpu_tmp0, cpu_cc_dst, 0x80000000);
                tcg_gen_brcondi_tl(inv ? TCG_COND_EQ : TCG_COND_NE, cpu_tmp0,
                                   0, l1);
                break;
#endif
            default:
                tcg_gen_brcondi_tl(inv ? TCG_COND_GE : TCG_COND_LT, cpu_cc_dst,
                                   0, l1);
                break;
            }
