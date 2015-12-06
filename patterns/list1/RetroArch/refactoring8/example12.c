const char* const input_builtin_autoconfs[] =
{
#ifdef VITA
   DECL_AUTOCONF_DEVICE("Vita Controller", "vita", PSPINPUT_DEFAULT_BINDS),
#else
   DECL_AUTOCONF_DEVICE("PSP Controller", "psp", PSPINPUT_DEFAULT_BINDS),
#endif
   NULL
};
