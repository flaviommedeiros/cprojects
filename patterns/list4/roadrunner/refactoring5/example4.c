#ifdef TCC_TARGET_COFF
if (s1->output_format == TCC_OUTPUT_FORMAT_COFF) {
        tcc_output_coff(s1, f);
    } else
#endif
    if (s1->output_format == TCC_OUTPUT_FORMAT_ELF) {
        sort_syms(s1, symtab_section);
        
        /* align to 4 */
        file_offset = (file_offset + 3) & -4;
    
        /* fill header */
        ehdr.e_ident[0] = ELFMAG0;
        ehdr.e_ident[1] = ELFMAG1;
        ehdr.e_ident[2] = ELFMAG2;
        ehdr.e_ident[3] = ELFMAG3;
        ehdr.e_ident[4] = TCC_ELFCLASS;
        ehdr.e_ident[5] = ELFDATA2LSB;
        ehdr.e_ident[6] = EV_CURRENT;
#ifdef __FreeBSD__
        ehdr.e_ident[EI_OSABI] = ELFOSABI_FREEBSD;
#endif
#ifdef TCC_TARGET_ARM
#ifdef TCC_ARM_EABI
        ehdr.e_ident[EI_OSABI] = 0;
        ehdr.e_flags = 4 << 24;
#else
        ehdr.e_ident[EI_OSABI] = ELFOSABI_ARM;
#endif
#endif
        switch(file_type) {
        default:
        case TCC_OUTPUT_EXE:
            ehdr.e_type = ET_EXEC;
            break;
        case TCC_OUTPUT_DLL:
            ehdr.e_type = ET_DYN;
            break;
        case TCC_OUTPUT_OBJ:
            ehdr.e_type = ET_REL;
            break;
        }
        ehdr.e_machine = EM_TCC_TARGET;
        ehdr.e_version = EV_CURRENT;
        ehdr.e_shoff = file_offset;
        ehdr.e_ehsize = sizeof(ElfW(Ehdr));
        ehdr.e_shentsize = sizeof(ElfW(Shdr));
        ehdr.e_shnum = shnum;
        ehdr.e_shstrndx = shnum - 1;
        
        fwrite(&ehdr, 1, sizeof(ElfW(Ehdr)), f);
        fwrite(phdr, 1, phnum * sizeof(ElfW(Phdr)), f);
        offset = sizeof(ElfW(Ehdr)) + phnum * sizeof(ElfW(Phdr));

        for(i=1;i<s1->nb_sections;i++) {
            s = s1->sections[section_order[i]];
            if (s->sh_type != SHT_NOBITS) {
                while (offset < s->sh_offset) {
                    fputc(0, f);
                    offset++;
                }
                size = s->sh_size;
                fwrite(s->data, 1, size, f);
                offset += size;
            }
        }

        /* output section headers */
        while (offset < ehdr.e_shoff) {
            fputc(0, f);
            offset++;
        }
    
        for(i=0;i<s1->nb_sections;i++) {
            sh = &shdr;
            memset(sh, 0, sizeof(ElfW(Shdr)));
            s = s1->sections[i];
            if (s) {
                sh->sh_name = s->sh_name;
                sh->sh_type = s->sh_type;
                sh->sh_flags = s->sh_flags;
                sh->sh_entsize = s->sh_entsize;
                sh->sh_info = s->sh_info;
                if (s->link)
                    sh->sh_link = s->link->sh_num;
                sh->sh_addralign = s->sh_addralign;
                sh->sh_addr = s->sh_addr;
                sh->sh_offset = s->sh_offset;
                sh->sh_size = s->sh_size;
            }
            fwrite(sh, 1, sizeof(ElfW(Shdr)), f);
        }
    } else {
        tcc_output_binary(s1, f, section_order);
    }
