static struct my_option my_long_options[]=
{
#ifdef DBUG_OFF
  {"debug", '#', "This is a non-debug version. Catch this and exit",
   0, 0, 0, GET_DISABLED, OPT_ARG, 0, 0, 0, 0, 0, 0},
#else
  {"debug", '#', "Output debug log", &default_dbug_option,
   &default_dbug_option, 0, GET_STR, OPT_ARG, 0, 0, 0, 0, 0, 0},
#endif
  {"debug-info", 'T', "Print some debug info at exit.", &info_flag,
   &info_flag, 0, GET_BOOL, NO_ARG, 0, 0, 0, 0, 0, 0},
  {"help", '?', "Displays this help and exits.", 0, 0, 0, GET_NO_ARG,
   NO_ARG, 0, 0, 0, 0, 0, 0},
  {"version", 'V', "Prints version", 0, 0, 0, GET_NO_ARG,
   NO_ARG, 0, 0, 0, 0, 0, 0},
  {"charset", 'C', "Charset dir", &charsets_dir, &charsets_dir,
   0, GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"in_file", 'F', "Input file", &TXTFILE, &TXTFILE,
   0, GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"out_dir", 'D', "Output base directory", &DATADIRECTORY, &DATADIRECTORY,
   0, GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"out_file", 'O', "Output filename (errmsg.sys)", &OUTFILE,
   &OUTFILE, 0, GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"header_file", 'H', "mysqld_error.h file ", &HEADERFILE,
   &HEADERFILE, 0, GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"name_file", 'N', "mysqld_ername.h file ", &NAMEFILE,
   &NAMEFILE, 0, GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {"state_file", 'S', "sql_state.h file", &STATEFILE,
   &STATEFILE, 0, GET_STR, REQUIRED_ARG, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, GET_NO_ARG, NO_ARG, 0, 0, 0, 0, 0, 0}
};
