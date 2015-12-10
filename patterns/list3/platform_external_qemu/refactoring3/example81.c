switch((uint32_t)ECX) {
    case MSR_IA32_SYSENTER_CS:
        env->sysenter_cs = val & 0xffff;
        break;
    case MSR_IA32_SYSENTER_ESP:
        env->sysenter_esp = val;
        break;
    case MSR_IA32_SYSENTER_EIP:
        env->sysenter_eip = val;
        break;
    case MSR_IA32_APICBASE:
        cpu_set_apic_base(env, val);
        break;
    case MSR_EFER:
        {
            uint64_t update_mask;
            update_mask = 0;
            if (env->cpuid_ext2_features & CPUID_EXT2_SYSCALL)
                update_mask |= MSR_EFER_SCE;
            if (env->cpuid_ext2_features & CPUID_EXT2_LM)
                update_mask |= MSR_EFER_LME;
            if (env->cpuid_ext2_features & CPUID_EXT2_FFXSR)
                update_mask |= MSR_EFER_FFXSR;
            if (env->cpuid_ext2_features & CPUID_EXT2_NX)
                update_mask |= MSR_EFER_NXE;
            if (env->cpuid_ext3_features & CPUID_EXT3_SVM)
                update_mask |= MSR_EFER_SVME;
            if (env->cpuid_ext2_features & CPUID_EXT2_FFXSR)
                update_mask |= MSR_EFER_FFXSR;
            cpu_load_efer(env, (env->efer & ~update_mask) |
                          (val & update_mask));
        }
        break;
    case MSR_STAR:
        env->star = val;
        break;
    case MSR_PAT:
        env->pat = val;
        break;
    case MSR_VM_HSAVE_PA:
        env->vm_hsave = val;
        break;
#ifdef TARGET_X86_64
    case MSR_LSTAR:
        env->lstar = val;
        break;
    case MSR_CSTAR:
        env->cstar = val;
        break;
    case MSR_FMASK:
        env->fmask = val;
        break;
    case MSR_FSBASE:
        env->segs[R_FS].base = val;
        break;
    case MSR_GSBASE:
        env->segs[R_GS].base = val;
        break;
    case MSR_KERNELGSBASE:
        env->kernelgsbase = val;
        break;
#endif
    case MSR_MTRRphysBase(0):
    case MSR_MTRRphysBase(1):
    case MSR_MTRRphysBase(2):
    case MSR_MTRRphysBase(3):
    case MSR_MTRRphysBase(4):
    case MSR_MTRRphysBase(5):
    case MSR_MTRRphysBase(6):
    case MSR_MTRRphysBase(7):
        env->mtrr_var[((uint32_t)ECX - MSR_MTRRphysBase(0)) / 2].base = val;
        break;
    case MSR_MTRRphysMask(0):
    case MSR_MTRRphysMask(1):
    case MSR_MTRRphysMask(2):
    case MSR_MTRRphysMask(3):
    case MSR_MTRRphysMask(4):
    case MSR_MTRRphysMask(5):
    case MSR_MTRRphysMask(6):
    case MSR_MTRRphysMask(7):
        env->mtrr_var[((uint32_t)ECX - MSR_MTRRphysMask(0)) / 2].mask = val;
        break;
    case MSR_MTRRfix64K_00000:
        env->mtrr_fixed[(uint32_t)ECX - MSR_MTRRfix64K_00000] = val;
        break;
    case MSR_MTRRfix16K_80000:
    case MSR_MTRRfix16K_A0000:
        env->mtrr_fixed[(uint32_t)ECX - MSR_MTRRfix16K_80000 + 1] = val;
        break;
    case MSR_MTRRfix4K_C0000:
    case MSR_MTRRfix4K_C8000:
    case MSR_MTRRfix4K_D0000:
    case MSR_MTRRfix4K_D8000:
    case MSR_MTRRfix4K_E0000:
    case MSR_MTRRfix4K_E8000:
    case MSR_MTRRfix4K_F0000:
    case MSR_MTRRfix4K_F8000:
        env->mtrr_fixed[(uint32_t)ECX - MSR_MTRRfix4K_C0000 + 3] = val;
        break;
    case MSR_MTRRdefType:
        env->mtrr_deftype = val;
        break;
    case MSR_MCG_STATUS:
        env->mcg_status = val;
        break;
    case MSR_MCG_CTL:
        if ((env->mcg_cap & MCG_CTL_P)
            && (val == 0 || val == ~(uint64_t)0))
            env->mcg_ctl = val;
        break;
    default:
        if ((uint32_t)ECX >= MSR_MC0_CTL
            && (uint32_t)ECX < MSR_MC0_CTL + (4 * env->mcg_cap & 0xff)) {
            uint32_t offset = (uint32_t)ECX - MSR_MC0_CTL;
            if ((offset & 0x3) != 0
                || (val == 0 || val == ~(uint64_t)0))
                env->mce_banks[offset] = val;
            break;
        }
        /* XXX: exception ? */
        break;
    }
