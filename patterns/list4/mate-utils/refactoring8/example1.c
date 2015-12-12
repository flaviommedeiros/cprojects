static GOptionEntry gdict_args[] = {
#ifdef GDICT_ENABLE_DEBUG
  { "gdict-debug", 0, 0, G_OPTION_ARG_CALLBACK, gdict_arg_debug_cb,
    N_("GDict debugging flags to set"), N_("FLAGS") },
  { "gdict-no-debug", 0, 0, G_OPTION_ARG_CALLBACK, gdict_arg_no_debug_cb,
    N_("GDict debugging flags to unset"), N_("FLAGS") },
#endif /* GDICT_ENABLE_DEBUG */
  { NULL, },
};
