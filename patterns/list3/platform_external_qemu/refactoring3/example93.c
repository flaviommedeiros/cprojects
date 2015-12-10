switch(size) {
            case 0:
                t0 = cpu_tmp0;
                tcg_gen_ext8s_tl(cpu_tmp4, cpu_tmp4);
                tcg_gen_ext8s_tl(t0, cpu_cc_src);
                break;
            case 1:
                t0 = cpu_tmp0;
                tcg_gen_ext16s_tl(cpu_tmp4, cpu_tmp4);
                tcg_gen_ext16s_tl(t0, cpu_cc_src);
                break;
#ifdef TARGET_X86_64
            case 2:
                t0 = cpu_tmp0;
                tcg_gen_ext32s_tl(cpu_tmp4, cpu_tmp4);
                tcg_gen_ext32s_tl(t0, cpu_cc_src);
                break;
#endif
            default:
                t0 = cpu_cc_src;
                break;
            }
