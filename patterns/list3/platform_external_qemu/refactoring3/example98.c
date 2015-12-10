switch(ot) {
            case OT_BYTE:
                gen_jmp_im(pc_start - s->cs_base);
                gen_helper_divb_AL(cpu_T[0]);
                break;
            case OT_WORD:
                gen_jmp_im(pc_start - s->cs_base);
                gen_helper_divw_AX(cpu_T[0]);
                break;
            default:
            case OT_LONG:
                gen_jmp_im(pc_start - s->cs_base);
                gen_helper_divl_EAX(cpu_T[0]);
                break;
#ifdef TARGET_X86_64
            case OT_QUAD:
                gen_jmp_im(pc_start - s->cs_base);
                gen_helper_divq_EAX(cpu_T[0]);
                break;
#endif
            }
