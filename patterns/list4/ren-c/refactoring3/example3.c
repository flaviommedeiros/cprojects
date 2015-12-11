switch (VAL_WORD_CANON(blk)) {
                            case SYM_DEFAULT:
                                VAL_ROUTINE_ABI(out) = FFI_DEFAULT_ABI;
                                break;
#ifdef X86_WIN64
                            case SYM_WIN64:
                                VAL_ROUTINE_ABI(out) = FFI_WIN64;
                                break;
#elif defined(X86_WIN32) || defined(TO_LINUX_X86) || defined(TO_LINUX_X64)
                            case SYM_STDCALL:
                                VAL_ROUTINE_ABI(out) = FFI_STDCALL;
                                break;
                            case SYM_SYSV:
                                VAL_ROUTINE_ABI(out) = FFI_SYSV;
                                break;
                            case SYM_THISCALL:
                                VAL_ROUTINE_ABI(out) = FFI_THISCALL;
                                break;
                            case SYM_FASTCALL:
                                VAL_ROUTINE_ABI(out) = FFI_FASTCALL;
                                break;
#ifdef X86_WIN32
                            case SYM_MS_CDECL:
                                VAL_ROUTINE_ABI(out) = FFI_MS_CDECL;
                                break;
#else
                            case SYM_UNIX64:
                                VAL_ROUTINE_ABI(out) = FFI_UNIX64;
                                break;
#endif //X86_WIN32
#elif defined (TO_LINUX_ARM)
                            case SYM_VFP:
                                VAL_ROUTINE_ABI(out) = FFI_VFP;
                            case SYM_SYSV:
                                VAL_ROUTINE_ABI(out) = FFI_SYSV;
                                break;
#elif defined (TO_LINUX_MIPS)
                            case SYM_O32:
                                VAL_ROUTINE_ABI(out) = FFI_O32;
                                break;
                            case SYM_N32:
                                VAL_RNUTINE_ABI(out) = FFI_N32;
                                break;
                            case SYM_N64:
                                VAL_RNUTINE_ABI(out) = FFI_N64;
                                break;
                            case SYM_O32_SOFT_FLOAT:
                                VAL_ROUTINE_ABI(out) = FFI_O32_SOFT_FLOAT;
                                break;
                            case SYM_N32_SOFT_FLOAT:
                                VAL_RNUTINE_ABI(out) = FFI_N32_SOFT_FLOAT;
                                break;
                            case SYM_N64_SOFT_FLOAT:
                                VAL_RNUTINE_ABI(out) = FFI_N64_SOFT_FLOAT;
                                break;
#endif //X86_WIN64
                            default:
                                fail (Error_Invalid_Arg(blk));
                        }
