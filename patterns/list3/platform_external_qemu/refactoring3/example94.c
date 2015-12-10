switch (ot) {
        case 0: gen_helper_rcrb(cpu_T[0], cpu_T[0], cpu_T[1]); break;
        case 1: gen_helper_rcrw(cpu_T[0], cpu_T[0], cpu_T[1]); break;
        case 2: gen_helper_rcrl(cpu_T[0], cpu_T[0], cpu_T[1]); break;
#ifdef TARGET_X86_64
        case 3: gen_helper_rcrq(cpu_T[0], cpu_T[0], cpu_T[1]); break;
#endif
        }
