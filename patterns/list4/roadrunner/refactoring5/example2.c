#ifdef TCC_TARGET_PE
if (output_type == TCC_OUTPUT_DLL)
                strcpy(ext, ".dll");
            else
            if (output_type == TCC_OUTPUT_EXE)
                strcpy(ext, ".exe");
            else
#endif
            if (output_type == TCC_OUTPUT_OBJ && !reloc_output && *ext)
                strcpy(ext, ".o");
            else
                pstrcpy(objfilename, sizeof(objfilename), "a.out");
