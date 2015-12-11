switch (cif->abi)
    {
#ifndef POWERPC64
    case FFI_SYSV:
    case FFI_GCC_SYSV:
    case FFI_LINUX:
    case FFI_LINUX_SOFT_FLOAT:
      ffi_call_SYSV (&ecif, -cif->bytes, cif->flags, ecif.rvalue, fn);
      break;
#else
    case FFI_LINUX64:
      ffi_call_LINUX64 (&ecif, -(long) cif->bytes, cif->flags, ecif.rvalue, fn);
      break;
#endif
    default:
      FFI_ASSERT (0);
      break;
    }
