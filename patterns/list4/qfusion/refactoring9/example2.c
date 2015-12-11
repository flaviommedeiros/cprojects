static void _state(struct connectdata *conn,
                   ftpstate newstate
#ifdef DEBUGBUILD
                   , int lineno
#endif
  )
{
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  /* for debug purposes */
  static const char * const names[]={
    "STOP",
    "WAIT220",
    "AUTH",
    "USER",
    "PASS",
    "ACCT",
    "PBSZ",
    "PROT",
    "CCC",
    "PWD",
    "SYST",
    "NAMEFMT",
    "QUOTE",
    "RETR_PREQUOTE",
    "STOR_PREQUOTE",
    "POSTQUOTE",
    "CWD",
    "MKD",
    "MDTM",
    "TYPE",
    "LIST_TYPE",
    "RETR_TYPE",
    "STOR_TYPE",
    "SIZE",
    "RETR_SIZE",
    "STOR_SIZE",
    "REST",
    "RETR_REST",
    "PORT",
    "PRET",
    "PASV",
    "LIST",
    "RETR",
    "STOR",
    "QUIT"
  };
#endif
  struct ftp_conn *ftpc = &conn->proto.ftpc;
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  if(ftpc->state != newstate)
    infof(conn->data, "FTP %p (line %d) state change from %s to %s\n",
          (void *)ftpc, lineno, names[ftpc->state], names[newstate]);
#endif
  ftpc->state = newstate;
}
