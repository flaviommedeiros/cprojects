if (reloc_type ==
#ifdef TCC_TARGET_X86_64
            R_X86_64_JUMP_SLOT
#else
            R_386_JMP_SLOT
#endif
            ) {
            Section *plt;
            uint8_t *p;
            int modrm;

#if defined(TCC_OUTPUT_DLL_WITH_PLT)
            modrm = 0x25;
#else
            /* if we build a DLL, we add a %ebx offset */
            if (s1->output_type == TCC_OUTPUT_DLL)
                modrm = 0xa3;
            else
                modrm = 0x25;
#endif

            /* add a PLT entry */
            plt = s1->plt;
            if (plt->data_offset == 0) {
                /* first plt entry */
                p = section_ptr_add(plt, 16);
                p[0] = 0xff; /* pushl got + PTR_SIZE */
                p[1] = modrm + 0x10;
                put32(p + 2, PTR_SIZE);
                p[6] = 0xff; /* jmp *(got + PTR_SIZE * 2) */
                p[7] = modrm;
                put32(p + 8, PTR_SIZE * 2);
            }

            p = section_ptr_add(plt, 16);
            p[0] = 0xff; /* jmp *(got + x) */
            p[1] = modrm;
            put32(p + 2, s1->got->data_offset);
            p[6] = 0x68; /* push $xxx */
            put32(p + 7, (plt->data_offset - 32) >> 1);
            p[11] = 0xe9; /* jmp plt_start */
            put32(p + 12, -(plt->data_offset));

            /* the symbol is modified so that it will be relocated to
               the PLT */
#if !defined(TCC_OUTPUT_DLL_WITH_PLT)
            if (s1->output_type == TCC_OUTPUT_EXE)
#endif
                offset = plt->data_offset - 16;
        }
