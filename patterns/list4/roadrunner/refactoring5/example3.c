#ifdef TCC_TARGET_PE
if (v >= 4096) {
        Sym *sym = external_global_sym(TOK___chkstk, &func_old_type, 0);
        oad(0xb8, v); /* mov stacksize, %eax */
        oad(0xe8, -4); /* call __chkstk, (does the stackframe too) */
        greloc(cur_text_section, sym, ind-4, R_X86_64_PC32);
    } else
#endif
    {
        o(0xe5894855);  /* push %rbp, mov %rsp, %rbp */
        o(0xec8148);  /* sub rsp, stacksize */
        gen_le32(v);
#if FUNC_PROLOG_SIZE == 12
        o(0x90);  /* adjust to FUNC_PROLOG_SIZE */
#endif
    }
