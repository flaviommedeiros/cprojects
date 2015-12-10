switch(size) {
            case 0:
                tcg_gen_andi_tl(cpu_tmp0, cpu_cc_dst, 0xff);
                t0 = cpu_tmp0;
                break;
            case 1:
                tcg_gen_andi_tl(cpu_tmp0, cpu_cc_dst, 0xffff);
                t0 = cpu_tmp0;
                break;
#ifdef TARGET_X86_64
            case 2:
                tcg_gen_andi_tl(cpu_tmp0, cpu_cc_dst, 0xffffffff);
                t0 = cpu_tmp0;
                break;
#endif
            default:
                t0 = cpu_cc_dst;
                break;
            }
