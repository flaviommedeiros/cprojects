#ifdef TCC_TARGET_PE
if (!PATHCMP(ext, "def")) {
        ret = pe_load_def_file(s1, file->fd);
    } else
#endif
    {
        fd = file->fd;
        /* assume executable format: auto guess file type */
        ret = read(fd, &ehdr, sizeof(ehdr));
        lseek(fd, 0, SEEK_SET);
        if (ret <= 0) {
            error_noabort("could not read header");
            goto fail;
        } else if (ret != sizeof(ehdr)) {
            goto try_load_script;
        }

        if (ehdr.e_ident[0] == ELFMAG0 &&
            ehdr.e_ident[1] == ELFMAG1 &&
            ehdr.e_ident[2] == ELFMAG2 &&
            ehdr.e_ident[3] == ELFMAG3) {
            file->line_num = 0; /* do not display line number if error */
            if (ehdr.e_type == ET_REL) {
                ret = tcc_load_object_file(s1, fd, 0);
            } else if (ehdr.e_type == ET_DYN) {
                if (s1->output_type == TCC_OUTPUT_MEMORY) {
#ifdef TCC_TARGET_PE
                    ret = -1;
#else
                    void *h;
                    h = dlopen(filename, RTLD_GLOBAL | RTLD_LAZY);
                    if (h)
                        ret = 0;
                    else
                        ret = -1;
#endif
                } else {
                    ret = tcc_load_dll(s1, fd, filename, 
                                       (flags & AFF_REFERENCED_DLL) != 0);
                }
            } else {
                error_noabort("unrecognized ELF file");
                goto fail;
            }
        } else if (memcmp((char *)&ehdr, ARMAG, 8) == 0) {
            file->line_num = 0; /* do not display line number if error */
            ret = tcc_load_archive(s1, fd);
        } else 
#ifdef TCC_TARGET_COFF
        if (*(uint16_t *)(&ehdr) == COFF_C67_MAGIC) {
            ret = tcc_load_coff(s1, fd);
        } else
#endif
#ifdef TCC_TARGET_PE
        if (pe_test_res_file(&ehdr, ret)) {
            ret = pe_load_res_file(s1, fd);
        } else
#endif
        {
            /* as GNU ld, consider it is an ld script if not recognized */
        try_load_script:
            ret = tcc_load_ldscript(s1);
            if (ret < 0) {
                error_noabort("unrecognized file type");
                goto fail;
            }
        }
    }
