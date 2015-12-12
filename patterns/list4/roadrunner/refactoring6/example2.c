if (file_type == TCC_OUTPUT_EXE
#if defined(TCC_OUTPUT_DLL_WITH_PLT)
                || file_type == TCC_OUTPUT_DLL
#endif
                ) {
                uint8_t *p, *p_end;

                p = s1->plt->data;
                p_end = p + s1->plt->data_offset;
                if (p < p_end) {
#if defined(TCC_TARGET_I386)
                    put32(p + 2, get32(p + 2) + s1->got->sh_addr);
                    put32(p + 8, get32(p + 8) + s1->got->sh_addr);
                    p += 16;
                    while (p < p_end) {
                        put32(p + 2, get32(p + 2) + s1->got->sh_addr);
                        p += 16;
                    }
#elif defined(TCC_TARGET_X86_64)
                    int x = s1->got->sh_addr - s1->plt->sh_addr - 6;
                    put32(p + 2, get32(p + 2) + x);
                    put32(p + 8, get32(p + 8) + x - 6);
                    p += 16;
                    while (p < p_end) {
                        put32(p + 2, get32(p + 2) + x + s1->plt->data - p);
                        p += 16;
                    }
#elif defined(TCC_TARGET_ARM)
                    int x;
                    x=s1->got->sh_addr - s1->plt->sh_addr - 12;
                    p +=16;
                    while (p < p_end) {
                        put32(p + 12, x + get32(p + 12) + s1->plt->data - p);
                        p += 16;
                    }
#elif defined(TCC_TARGET_C67)
                    /* XXX: TODO */
#else
#error unsupported CPU
#endif
                }
            }
