switch (msrs[i].index) {
        case MSR_IA32_SYSENTER_CS:
            env->sysenter_cs = msrs[i].data;
            break;
        case MSR_IA32_SYSENTER_ESP:
            env->sysenter_esp = msrs[i].data;
            break;
        case MSR_IA32_SYSENTER_EIP:
            env->sysenter_eip = msrs[i].data;
            break;
        case MSR_STAR:
            env->star = msrs[i].data;
            break;
#ifdef TARGET_X86_64
        case MSR_CSTAR:
            env->cstar = msrs[i].data;
            break;
        case MSR_KERNELGSBASE:
            env->kernelgsbase = msrs[i].data;
            break;
        case MSR_FMASK:
            env->fmask = msrs[i].data;
            break;
        case MSR_LSTAR:
            env->lstar = msrs[i].data;
            break;
#endif
        case MSR_IA32_TSC:
            env->tsc = msrs[i].data;
            break;
        }
