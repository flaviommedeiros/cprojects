#ifdef TCC_TARGET_COFF
if (!strcmp(p, "coff")) {
                            s->output_format = TCC_OUTPUT_FORMAT_COFF;
                        } else
#endif
                        {
                            error("target %s not found", p);
                        }
