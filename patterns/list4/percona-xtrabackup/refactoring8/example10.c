static struct my_option my_long_options[] =
{
  /*
    NB: --config-file is troublesome, because get_defaults_options() doesn't
    know about it, but we pretend --config-file is like --defaults-file.  In
    fact they behave differently: see the comments at the top of
    mysys/default.c for how --defaults-file should behave.

    This --config-file option behaves as:
    - If it has a directory name part (absolute or relative), then only this
      file is read; no error is given if the file doesn't exist
    - If the file has no directory name part, the standard locations are
      searched for a file of this name (and standard filename extensions are
      added if the file has no extension)
  */
  {"config-file", 'c', "Deprecated, please use --defaults-file instead. "
   "Name of config file to read; if no extension is given, default "
   "extension (e.g., .ini or .cnf) will be added",
   &config_file, &config_file, 0, GET_STR, REQUIRED_ARG,
   0, 0, 0, 0, 0, 0},
#ifdef DBUG_OFF
  {"debug", '#', "This is a non-debug version. Catch this and exit",
   0,0, 0, GET_DISABLED, OPT_ARG, 0, 0, 0, 0, 0, 0},
#else
  {"debug", '#', "Output debug log", &default_dbug_option,
   &default_dbug_option, 0, GET_STR, OPT_ARG, 0, 0, 0, 0, 0, 0},
#endif
  {"defaults-file", 'c', "Like --config-file, except: if first option, "
   "then read this file only, do not read global or per-user config "
   "files; should be the first option",
   &config_file, &config_file, 0, GET_STR, REQUIRED_ARG,
   0, 0, 0, 0, 0, 0},
  {"defaults-extra-file", 'e',
   "Read this file after the global config file and before the config "
   "file in the users home directory; should be the first option",
   &my_defaults_extra_file, &my_defaults_extra_file, 0,
   GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"defaults-group-suffix", 'g',
   "In addition to the given groups, read also groups with this suffix",
   &my_defaults_group_suffix, &my_defaults_group_suffix,
   0, GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"extra-file", 'e',
   "Deprecated. Synonym for --defaults-extra-file.",
   &my_defaults_extra_file,
   &my_defaults_extra_file, 0, GET_STR,
   REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"no-defaults", 'n', "Ignore reading of default option file(s), "
   "except for login file.", 0, 0, 0, GET_NO_ARG, NO_ARG, 0, 0, 0,
   0, 0, 0},
  {"login-path", 'l', "Path to be read from under the login file.",
   &my_login_path, &my_login_path, 0, GET_STR, REQUIRED_ARG,
   0, 0, 0, 0, 0, 0},
  {"help", '?', "Display this help message and exit.",
   0, 0, 0, GET_NO_ARG, NO_ARG, 0, 0, 0, 0, 0, 0},
  {"verbose", 'v', "Increase the output level",
   0, 0, 0, GET_NO_ARG, NO_ARG, 0, 0, 0, 0, 0, 0},
  {"version", 'V', "Output version information and exit.",
   0, 0, 0, GET_NO_ARG, NO_ARG, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, GET_NO_ARG, NO_ARG, 0, 0, 0, 0, 0, 0}
};
