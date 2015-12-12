#ifdef TCC_TARGET_PE
if (s->output_type != TCC_OUTPUT_OBJ) {
        ret = pe_output_file(s, filename);
    } else
#endif
    {
        ret = elf_output_file(s, filename);
    }
