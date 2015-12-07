#ifdef __linux
if (uname(&uts) == 0 && strcmp(uts.machine, "ppc64") == 0)
#endif
            if (sigsetjmp(ill_jmp, 1) == 0) {
                OPENSSL_ppc64_probe();
                OPENSSL_ppccap_P |= PPC_FPU64;
            }
