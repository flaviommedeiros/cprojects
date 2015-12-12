switch (cif->abi) 
    {
#ifdef X86_WIN32
    case FFI_SYSV:
    case FFI_STDCALL:
      ffi_call_win32(ffi_prep_args_raw, &ecif, cif->bytes, cif->flags,
                     ecif.rvalue, fn);
      break;
#else
    case FFI_SYSV:
      ffi_call_SYSV(ffi_prep_args_raw, &ecif, cif->bytes, cif->flags,
                    ecif.rvalue, fn);
      break;
#endif
    default:
      FFI_ASSERT(0);
      break;
    }
