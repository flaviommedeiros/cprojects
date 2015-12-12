switch(popt->index) {
            case TCC_OPTION_HELP:
                return 0;

            case TCC_OPTION_I:
                if (tcc_add_include_path(s, optarg) < 0)
                    error("too many include paths");
                break;
            case TCC_OPTION_D:
                {
                    char *sym, *value;
                    sym = (char *)optarg;
                    value = strchr(sym, '=');
                    if (value) {
                        *value = '\0';
                        value++;
                    }
                    tcc_define_symbol(s, sym, value);
                }
                break;
            case TCC_OPTION_U:
                tcc_undefine_symbol(s, optarg);
                break;
            case TCC_OPTION_L:
                tcc_add_library_path(s, optarg);
                break;
            case TCC_OPTION_B:
                /* set tcc utilities path (mainly for tcc development) */
                tcc_set_lib_path(s, optarg);
                break;
            case TCC_OPTION_l:
                dynarray_add((void ***)&files, &nb_files, r);
                nb_libraries++;
                break;
            case TCC_OPTION_bench:
                do_bench = 1;
                break;
#ifdef CONFIG_TCC_BACKTRACE
            case TCC_OPTION_bt:
                num_callers = atoi(optarg);
                break;
#endif
#ifdef CONFIG_TCC_BCHECK
            case TCC_OPTION_b:
                s->do_bounds_check = 1;
                s->do_debug = 1;
                break;
#endif
            case TCC_OPTION_g:
                s->do_debug = 1;
                break;
            case TCC_OPTION_c:
                multiple_files = 1;
                output_type = TCC_OUTPUT_OBJ;
                break;
            case TCC_OPTION_static:
                s->static_link = 1;
                break;
            case TCC_OPTION_shared:
                output_type = TCC_OUTPUT_DLL;
                break;
            case TCC_OPTION_soname:
                s->soname = optarg; 
                break;
            case TCC_OPTION_o:
                multiple_files = 1;
                outfile = optarg;
                break;
            case TCC_OPTION_r:
                /* generate a .o merging several output files */
                reloc_output = 1;
                output_type = TCC_OUTPUT_OBJ;
                break;
            case TCC_OPTION_nostdinc:
                s->nostdinc = 1;
                break;
            case TCC_OPTION_nostdlib:
                s->nostdlib = 1;
                break;
            case TCC_OPTION_print_search_dirs:
                print_search_dirs = 1;
                break;
            case TCC_OPTION_run:
                {
                    int argc1;
                    char **argv1;
                    argc1 = expand_args(&argv1, optarg);
                    if (argc1 > 0) {
                        parse_args(s, argc1, argv1);
                    }
                    multiple_files = 0;
                    output_type = TCC_OUTPUT_MEMORY;
                }
                break;
            case TCC_OPTION_v:
                do {
                    if (0 == s->verbose++)
                        printf("tcc version %s\n", TCC_VERSION);
                } while (*optarg++ == 'v');
                break;
            case TCC_OPTION_f:
                if (tcc_set_flag(s, optarg, 1) < 0 && s->warn_unsupported)
                    goto unsupported_option;
                break;
            case TCC_OPTION_W:
                if (tcc_set_warning(s, optarg, 1) < 0 && 
                    s->warn_unsupported)
                    goto unsupported_option;
                break;
            case TCC_OPTION_w:
                s->warn_none = 1;
                break;
            case TCC_OPTION_rdynamic:
                s->rdynamic = 1;
                break;
            case TCC_OPTION_Wl:
                {
                    const char *p;
                    if (strstart(optarg, "-Ttext,", &p)) {
                        s->text_addr = strtoul(p, NULL, 16);
                        s->has_text_addr = 1;
                    } else if (strstart(optarg, "--oformat,", &p)) {
                        if (strstart(p, "elf32-", NULL)) {
                            s->output_format = TCC_OUTPUT_FORMAT_ELF;
                        } else if (!strcmp(p, "binary")) {
                            s->output_format = TCC_OUTPUT_FORMAT_BINARY;
                        } else
#ifdef TCC_TARGET_COFF
                        if (!strcmp(p, "coff")) {
                            s->output_format = TCC_OUTPUT_FORMAT_COFF;
                        } else
#endif
                        {
                            error("target %s not found", p);
                        }
                    } else {
                        error("unsupported linker option '%s'", optarg);
                    }
                }
                break;
            case TCC_OPTION_E:
                output_type = TCC_OUTPUT_PREPROCESS;
                break;
            default:
                if (s->warn_unsupported) {
                unsupported_option:
                    warning("unsupported option '%s'", r);
                }
                break;
            }
