static const GumFFIABIMapping gum_ffi_abi_mappings[] =
{
  { "default", FFI_DEFAULT_ABI },
#if defined (X86_WIN64)
  { "win64", FFI_WIN64 },
#elif defined (X86_ANY) && GLIB_SIZEOF_VOID_P == 8
  { "unix64", FFI_UNIX64 },
#elif defined (X86_ANY) && GLIB_SIZEOF_VOID_P == 4
  { "sysv", FFI_SYSV },
  { "stdcall", FFI_STDCALL },
  { "thiscall", FFI_THISCALL },
  { "fastcall", FFI_FASTCALL },
# if defined (X86_WIN32)
  { "mscdecl", FFI_MS_CDECL },
# endif
#elif defined (ARM)
  { "sysv", FFI_SYSV },
# if GLIB_SIZEOF_VOID_P == 4
  { "vfp", FFI_VFP },
# endif
#endif
};
