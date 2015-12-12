if (sh->sh_type != SHT_PROGBITS &&
            sh->sh_type != SHT_RELX && 
#ifdef TCC_ARM_EABI
            sh->sh_type != SHT_ARM_EXIDX &&
#endif
            sh->sh_type != SHT_NOBITS && 
            strcmp(sh_name, ".stabstr")
            )
            continue;
