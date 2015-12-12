static char* args[] = { "--gemm",               // 0
                            "--trmm",               // 1
                            "--trsm",               // 2
                            "--buffers",            // 3
                            "--images",             // 4
                            "--float",              // 5
                            "--double",             // 6
                            "--complex",            // 7
                            "--double-complex",     // 8
                            "--store-kernels",      // 9
                            "--rebuild",            // 10
#if defined(_EXTENDED_TUNE_ARG)
                            "--e",                  // 11
                            "--max",                // 12
                            "--extended-output",    // 13
#else
                            "",
                            "",
                            "",
#endif
                            "--gemv",               // 14
                            "--symv",               // 15
                            "--syrk",               // 20
                            "--syr2k",              // 17
                            "--fast",               // 18
                            "--caches",             // 19
                            "--help"                // 20
                            };
