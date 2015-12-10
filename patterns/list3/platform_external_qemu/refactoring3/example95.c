switch (ot) {
        case 0: gen_helper_rclb(cpu_T[0], cpu_T[0], cpu_T[1]); break;
        case 1: gen_helper_rclw(cpu_T[0], cpu_T[0], cpu_T[1]); break;
        case 2: gen_helper_rcll(cpu_T[0], cpu_T[0], cpu_T[1]); break;
#ifdef TARGET_X86_64
        case 3: gen_helper_rclq(cpu_T[0], cpu_T[0], cpu_T[1]); break;
#endif
        }
