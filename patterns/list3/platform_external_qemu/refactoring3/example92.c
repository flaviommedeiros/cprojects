switch(size) {
            case 0:
                t0 = cpu_tmp0;
                tcg_gen_andi_tl(cpu_tmp4, cpu_tmp4, 0xff);
                tcg_gen_andi_tl(t0, cpu_cc_src, 0xff);
                break;
            case 1:
                t0 = cpu_tmp0;
                tcg_gen_andi_tl(cpu_tmp4, cpu_tmp4, 0xffff);
                tcg_gen_andi_tl(t0, cpu_cc_src, 0xffff);
                break;
#ifdef TARGET_X86_64
            case 2:
                t0 = cpu_tmp0;
                tcg_gen_andi_tl(cpu_tmp4, cpu_tmp4, 0xffffffff);
                tcg_gen_andi_tl(t0, cpu_cc_src, 0xffffffff);
                break;
#endif
            default:
                t0 = cpu_cc_src;
                break;
            }
