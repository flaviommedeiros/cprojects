switch(ot) {
            case OT_BYTE:
                gen_jmp_im(pc_start - s->cs_base);
                gen_helper_idivb_AL(cpu_T[0]);
                break;
            case OT_WORD:
                gen_jmp_im(pc_start - s->cs_base);
                gen_helper_idivw_AX(cpu_T[0]);
                break;
            default:
            case OT_LONG:
                gen_jmp_im(pc_start - s->cs_base);
                gen_helper_idivl_EAX(cpu_T[0]);
                break;
#ifdef TARGET_X86_64
            case OT_QUAD:
                gen_jmp_im(pc_start - s->cs_base);
                gen_helper_idivq_EAX(cpu_T[0]);
                break;
#endif
            }
