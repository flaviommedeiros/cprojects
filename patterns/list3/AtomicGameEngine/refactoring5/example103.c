#ifndef SQLITE_OMIT_LOAD_EXTENSION
if( c=='l' && strncmp(azArg[0], "load", n)==0 ){
    const char *zFile, *zProc;
    char *zErrMsg = 0;
    if( nArg<2 ){
      fprintf(stderr, "Usage: .load FILE ?ENTRYPOINT?\n");
      rc = 1;
      goto meta_command_exit;
    }
    zFile = azArg[1];
    zProc = nArg>=3 ? azArg[2] : 0;
    open_db(p, 0);
    rc = sqlite3_load_extension(p->db, zFile, zProc, &zErrMsg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "Error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      rc = 1;
    }
  }else
#endif

  if( c=='l' && strncmp(azArg[0], "log", n)==0 ){
    if( nArg!=2 ){
      fprintf(stderr, "Usage: .log FILENAME\n");
      rc = 1;
    }else{
      const char *zFile = azArg[1];
      output_file_close(p->pLog);
      p->pLog = output_file_open(zFile);
    }
  }else

  if( c=='m' && strncmp(azArg[0], "mode", n)==0 ){
    const char *zMode = nArg>=2 ? azArg[1] : "";
    int n2 = (int)strlen(zMode);
    int c2 = zMode[0];
    if( c2=='l' && n2>2 && strncmp(azArg[1],"lines",n2)==0 ){
      p->mode = MODE_Line;
    }else if( c2=='c' && strncmp(azArg[1],"columns",n2)==0 ){
      p->mode = MODE_Column;
    }else if( c2=='l' && n2>2 && strncmp(azArg[1],"list",n2)==0 ){
      p->mode = MODE_List;
    }else if( c2=='h' && strncmp(azArg[1],"html",n2)==0 ){
      p->mode = MODE_Html;
    }else if( c2=='t' && strncmp(azArg[1],"tcl",n2)==0 ){
      p->mode = MODE_Tcl;
      sqlite3_snprintf(sizeof(p->colSeparator), p->colSeparator, SEP_Space);
    }else if( c2=='c' && strncmp(azArg[1],"csv",n2)==0 ){
      p->mode = MODE_Csv;
      sqlite3_snprintf(sizeof(p->colSeparator), p->colSeparator, SEP_Comma);
      sqlite3_snprintf(sizeof(p->rowSeparator), p->rowSeparator, SEP_CrLf);
    }else if( c2=='t' && strncmp(azArg[1],"tabs",n2)==0 ){
      p->mode = MODE_List;
      sqlite3_snprintf(sizeof(p->colSeparator), p->colSeparator, SEP_Tab);
    }else if( c2=='i' && strncmp(azArg[1],"insert",n2)==0 ){
      p->mode = MODE_Insert;
      set_table_name(p, nArg>=3 ? azArg[2] : "table");
    }else if( c2=='a' && strncmp(azArg[1],"ascii",n2)==0 ){
      p->mode = MODE_Ascii;
      sqlite3_snprintf(sizeof(p->colSeparator), p->colSeparator, SEP_Unit);
      sqlite3_snprintf(sizeof(p->rowSeparator), p->rowSeparator, SEP_Record);
    }else {
      fprintf(stderr,"Error: mode should be one of: "
         "ascii column csv html insert line list tabs tcl\n");
      rc = 1;
    }
  }else

  if( c=='n' && strncmp(azArg[0], "nullvalue", n)==0 ){
    if( nArg==2 ){
      sqlite3_snprintf(sizeof(p->nullValue), p->nullValue,
                       "%.*s", (int)ArraySize(p->nullValue)-1, azArg[1]);
    }else{
      fprintf(stderr, "Usage: .nullvalue STRING\n");
      rc = 1;
    }
  }else

  if( c=='o' && strncmp(azArg[0], "open", n)==0 && n>=2 ){
    sqlite3 *savedDb = p->db;
    const char *zSavedFilename = p->zDbFilename;
    char *zNewFilename = 0;
    p->db = 0;
    if( nArg>=2 ){
      p->zDbFilename = zNewFilename = sqlite3_mprintf("%s", azArg[1]);
    }
    open_db(p, 1);
    if( p->db!=0 ){
      sqlite3_close(savedDb);
      sqlite3_free(p->zFreeOnClose);
      p->zFreeOnClose = zNewFilename;
    }else{
      sqlite3_free(zNewFilename);
      p->db = savedDb;
      p->zDbFilename = zSavedFilename;
    }
  }else

  if( c=='o'
   && (strncmp(azArg[0], "output", n)==0 || strncmp(azArg[0], "once", n)==0)
  ){
    const char *zFile = nArg>=2 ? azArg[1] : "stdout";
    if( nArg>2 ){
      fprintf(stderr, "Usage: .%s FILE\n", azArg[0]);
      rc = 1;
      goto meta_command_exit;
    }
    if( n>1 && strncmp(azArg[0], "once", n)==0 ){
      if( nArg<2 ){
        fprintf(stderr, "Usage: .once FILE\n");
        rc = 1;
        goto meta_command_exit;
      }
      p->outCount = 2;
    }else{
      p->outCount = 0;
    }
    output_reset(p);
    if( zFile[0]=='|' ){
#ifdef SQLITE_OMIT_POPEN
      fprintf(stderr,"Error: pipes are not supported in this OS\n");
      rc = 1;
      p->out = stdout;
#else
      p->out = popen(zFile + 1, "w");
      if( p->out==0 ){
        fprintf(stderr,"Error: cannot open pipe \"%s\"\n", zFile + 1);
        p->out = stdout;
        rc = 1;
      }else{
        sqlite3_snprintf(sizeof(p->outfile), p->outfile, "%s", zFile);
      }
#endif
    }else{
      p->out = output_file_open(zFile);
      if( p->out==0 ){
        if( strcmp(zFile,"off")!=0 ){
          fprintf(stderr,"Error: cannot write to \"%s\"\n", zFile);
        }
        p->out = stdout;
        rc = 1;
      } else {
        sqlite3_snprintf(sizeof(p->outfile), p->outfile, "%s", zFile);
      }
    }
  }else

  if( c=='p' && n>=3 && strncmp(azArg[0], "print", n)==0 ){
    int i;
    for(i=1; i<nArg; i++){
      if( i>1 ) fprintf(p->out, " ");
      fprintf(p->out, "%s", azArg[i]);
    }
    fprintf(p->out, "\n");
  }else

  if( c=='p' && strncmp(azArg[0], "prompt", n)==0 ){
    if( nArg >= 2) {
      strncpy(mainPrompt,azArg[1],(int)ArraySize(mainPrompt)-1);
    }
    if( nArg >= 3) {
      strncpy(continuePrompt,azArg[2],(int)ArraySize(continuePrompt)-1);
    }
  }else

  if( c=='q' && strncmp(azArg[0], "quit", n)==0 ){
    rc = 2;
  }else

  if( c=='r' && n>=3 && strncmp(azArg[0], "read", n)==0 ){
    FILE *alt;
    if( nArg!=2 ){
      fprintf(stderr, "Usage: .read FILE\n");
      rc = 1;
      goto meta_command_exit;
    }
    alt = fopen(azArg[1], "rb");
    if( alt==0 ){
      fprintf(stderr,"Error: cannot open \"%s\"\n", azArg[1]);
      rc = 1;
    }else{
      rc = process_input(p, alt);
      fclose(alt);
    }
  }else

  if( c=='r' && n>=3 && strncmp(azArg[0], "restore", n)==0 ){
    const char *zSrcFile;
    const char *zDb;
    sqlite3 *pSrc;
    sqlite3_backup *pBackup;
    int nTimeout = 0;

    if( nArg==2 ){
      zSrcFile = azArg[1];
      zDb = "main";
    }else if( nArg==3 ){
      zSrcFile = azArg[2];
      zDb = azArg[1];
    }else{
      fprintf(stderr, "Usage: .restore ?DB? FILE\n");
      rc = 1;
      goto meta_command_exit;
    }
    rc = sqlite3_open(zSrcFile, &pSrc);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "Error: cannot open \"%s\"\n", zSrcFile);
      sqlite3_close(pSrc);
      return 1;
    }
    open_db(p, 0);
    pBackup = sqlite3_backup_init(p->db, zDb, pSrc, "main");
    if( pBackup==0 ){
      fprintf(stderr, "Error: %s\n", sqlite3_errmsg(p->db));
      sqlite3_close(pSrc);
      return 1;
    }
    while( (rc = sqlite3_backup_step(pBackup,100))==SQLITE_OK
          || rc==SQLITE_BUSY  ){
      if( rc==SQLITE_BUSY ){
        if( nTimeout++ >= 3 ) break;
        sqlite3_sleep(100);
      }
    }
    sqlite3_backup_finish(pBackup);
    if( rc==SQLITE_DONE ){
      rc = 0;
    }else if( rc==SQLITE_BUSY || rc==SQLITE_LOCKED ){
      fprintf(stderr, "Error: source database is busy\n");
      rc = 1;
    }else{
      fprintf(stderr, "Error: %s\n", sqlite3_errmsg(p->db));
      rc = 1;
    }
    sqlite3_close(pSrc);
  }else


  if( c=='s' && strncmp(azArg[0], "scanstats", n)==0 ){
    if( nArg==2 ){
      p->scanstatsOn = booleanValue(azArg[1]);
#ifndef SQLITE_ENABLE_STMT_SCANSTATUS
      fprintf(stderr, "Warning: .scanstats not available in this build.\n");
#endif
    }else{
      fprintf(stderr, "Usage: .scanstats on|off\n");
      rc = 1;
    }
  }else

  if( c=='s' && strncmp(azArg[0], "schema", n)==0 ){
    ShellState data;
    char *zErrMsg = 0;
    open_db(p, 0);
    memcpy(&data, p, sizeof(data));
    data.showHeader = 0;
    data.mode = MODE_Semi;
    if( nArg==2 ){
      int i;
      for(i=0; azArg[1][i]; i++) azArg[1][i] = ToLower(azArg[1][i]);
      if( strcmp(azArg[1],"sqlite_master")==0 ){
        char *new_argv[2], *new_colv[2];
        new_argv[0] = "CREATE TABLE sqlite_master (\n"
                      "  type text,\n"
                      "  name text,\n"
                      "  tbl_name text,\n"
                      "  rootpage integer,\n"
                      "  sql text\n"
                      ")";
        new_argv[1] = 0;
        new_colv[0] = "sql";
        new_colv[1] = 0;
        callback(&data, 1, new_argv, new_colv);
        rc = SQLITE_OK;
      }else if( strcmp(azArg[1],"sqlite_temp_master")==0 ){
        char *new_argv[2], *new_colv[2];
        new_argv[0] = "CREATE TEMP TABLE sqlite_temp_master (\n"
                      "  type text,\n"
                      "  name text,\n"
                      "  tbl_name text,\n"
                      "  rootpage integer,\n"
                      "  sql text\n"
                      ")";
        new_argv[1] = 0;
        new_colv[0] = "sql";
        new_colv[1] = 0;
        callback(&data, 1, new_argv, new_colv);
        rc = SQLITE_OK;
      }else{
        zShellStatic = azArg[1];
        rc = sqlite3_exec(p->db,
          "SELECT sql FROM "
          "  (SELECT sql sql, type type, tbl_name tbl_name, name name, rowid x"
          "     FROM sqlite_master UNION ALL"
          "   SELECT sql, type, tbl_name, name, rowid FROM sqlite_temp_master) "
          "WHERE lower(tbl_name) LIKE shellstatic()"
          "  AND type!='meta' AND sql NOTNULL "
          "ORDER BY rowid",
          callback, &data, &zErrMsg);
        zShellStatic = 0;
      }
    }else if( nArg==1 ){
      rc = sqlite3_exec(p->db,
         "SELECT sql FROM "
         "  (SELECT sql sql, type type, tbl_name tbl_name, name name, rowid x"
         "     FROM sqlite_master UNION ALL"
         "   SELECT sql, type, tbl_name, name, rowid FROM sqlite_temp_master) "
         "WHERE type!='meta' AND sql NOTNULL AND name NOT LIKE 'sqlite_%' "
         "ORDER BY rowid",
         callback, &data, &zErrMsg
      );
    }else{
      fprintf(stderr, "Usage: .schema ?LIKE-PATTERN?\n");
      rc = 1;
      goto meta_command_exit;
    }
    if( zErrMsg ){
      fprintf(stderr,"Error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      rc = 1;
    }else if( rc != SQLITE_OK ){
      fprintf(stderr,"Error: querying schema information\n");
      rc = 1;
    }else{
      rc = 0;
    }
  }else


#if defined(SQLITE_DEBUG) && defined(SQLITE_ENABLE_SELECTTRACE)
  if( c=='s' && n==11 && strncmp(azArg[0], "selecttrace", n)==0 ){
    extern int sqlite3SelectTrace;
    sqlite3SelectTrace = integerValue(azArg[1]);
  }else
#endif


#ifdef SQLITE_DEBUG
  /* Undocumented commands for internal testing.  Subject to change
  ** without notice. */
  if( c=='s' && n>=10 && strncmp(azArg[0], "selftest-", 9)==0 ){
    if( strncmp(azArg[0]+9, "boolean", n-9)==0 ){
      int i, v;
      for(i=1; i<nArg; i++){
        v = booleanValue(azArg[i]);
        fprintf(p->out, "%s: %d 0x%x\n", azArg[i], v, v);
      }
    }
    if( strncmp(azArg[0]+9, "integer", n-9)==0 ){
      int i; sqlite3_int64 v;
      for(i=1; i<nArg; i++){
        char zBuf[200];
        v = integerValue(azArg[i]);
        sqlite3_snprintf(sizeof(zBuf),zBuf,"%s: %lld 0x%llx\n", azArg[i],v,v);
        fprintf(p->out, "%s", zBuf);
      }
    }
  }else
#endif

  if( c=='s' && strncmp(azArg[0], "separator", n)==0 ){
    if( nArg<2 || nArg>3 ){
      fprintf(stderr, "Usage: .separator COL ?ROW?\n");
      rc = 1;
    }
    if( nArg>=2 ){
      sqlite3_snprintf(sizeof(p->colSeparator), p->colSeparator,
                       "%.*s", (int)ArraySize(p->colSeparator)-1, azArg[1]);
    }
    if( nArg>=3 ){
      sqlite3_snprintf(sizeof(p->rowSeparator), p->rowSeparator,
                       "%.*s", (int)ArraySize(p->rowSeparator)-1, azArg[2]);
    }
  }else

  if( c=='s'
   && (strncmp(azArg[0], "shell", n)==0 || strncmp(azArg[0],"system",n)==0)
  ){
    char *zCmd;
    int i, x;
    if( nArg<2 ){
      fprintf(stderr, "Usage: .system COMMAND\n");
      rc = 1;
      goto meta_command_exit;
    }
    zCmd = sqlite3_mprintf(strchr(azArg[1],' ')==0?"%s":"\"%s\"", azArg[1]);
    for(i=2; i<nArg; i++){
      zCmd = sqlite3_mprintf(strchr(azArg[i],' ')==0?"%z %s":"%z \"%s\"",
                             zCmd, azArg[i]);
    }
    x = system(zCmd);
    sqlite3_free(zCmd);
    if( x ) fprintf(stderr, "System command returns %d\n", x);
  }else

  if( c=='s' && strncmp(azArg[0], "show", n)==0 ){
    int i;
    if( nArg!=1 ){
      fprintf(stderr, "Usage: .show\n");
      rc = 1;
      goto meta_command_exit;
    }
    fprintf(p->out,"%12.12s: %s\n","echo", p->echoOn ? "on" : "off");
    fprintf(p->out,"%12.12s: %s\n","eqp", p->autoEQP ? "on" : "off");
    fprintf(p->out,"%9.9s: %s\n","explain", p->normalMode.valid ? "on" :"off");
    fprintf(p->out,"%12.12s: %s\n","headers", p->showHeader ? "on" : "off");
    fprintf(p->out,"%12.12s: %s\n","mode", modeDescr[p->mode]);
    fprintf(p->out,"%12.12s: ", "nullvalue");
      output_c_string(p->out, p->nullValue);
      fprintf(p->out, "\n");
    fprintf(p->out,"%12.12s: %s\n","output",
            strlen30(p->outfile) ? p->outfile : "stdout");
    fprintf(p->out,"%12.12s: ", "colseparator");
      output_c_string(p->out, p->colSeparator);
      fprintf(p->out, "\n");
    fprintf(p->out,"%12.12s: ", "rowseparator");
      output_c_string(p->out, p->rowSeparator);
      fprintf(p->out, "\n");
    fprintf(p->out,"%12.12s: %s\n","stats", p->statsOn ? "on" : "off");
    fprintf(p->out,"%12.12s: ","width");
    for (i=0;i<(int)ArraySize(p->colWidth) && p->colWidth[i] != 0;i++) {
      fprintf(p->out,"%d ",p->colWidth[i]);
    }
    fprintf(p->out,"\n");
  }else

  if( c=='s' && strncmp(azArg[0], "stats", n)==0 ){
    if( nArg==2 ){
      p->statsOn = booleanValue(azArg[1]);
    }else{
      fprintf(stderr, "Usage: .stats on|off\n");
      rc = 1;
    }
  }else

  if( c=='t' && n>1 && strncmp(azArg[0], "tables", n)==0 ){
    sqlite3_stmt *pStmt;
    char **azResult;
    int nRow, nAlloc;
    char *zSql = 0;
    int ii;
    open_db(p, 0);
    rc = sqlite3_prepare_v2(p->db, "PRAGMA database_list", -1, &pStmt, 0);
    if( rc ) return rc;
    zSql = sqlite3_mprintf(
        "SELECT name FROM sqlite_master"
        " WHERE type IN ('table','view')"
        "   AND name NOT LIKE 'sqlite_%%'"
        "   AND name LIKE ?1");
    while( sqlite3_step(pStmt)==SQLITE_ROW ){
      const char *zDbName = (const char*)sqlite3_column_text(pStmt, 1);
      if( zDbName==0 || strcmp(zDbName,"main")==0 ) continue;
      if( strcmp(zDbName,"temp")==0 ){
        zSql = sqlite3_mprintf(
                 "%z UNION ALL "
                 "SELECT 'temp.' || name FROM sqlite_temp_master"
                 " WHERE type IN ('table','view')"
                 "   AND name NOT LIKE 'sqlite_%%'"
                 "   AND name LIKE ?1", zSql);
      }else{
        zSql = sqlite3_mprintf(
                 "%z UNION ALL "
                 "SELECT '%q.' || name FROM \"%w\".sqlite_master"
                 " WHERE type IN ('table','view')"
                 "   AND name NOT LIKE 'sqlite_%%'"
                 "   AND name LIKE ?1", zSql, zDbName, zDbName);
      }
    }
    sqlite3_finalize(pStmt);
    zSql = sqlite3_mprintf("%z ORDER BY 1", zSql);
    rc = sqlite3_prepare_v2(p->db, zSql, -1, &pStmt, 0);
    sqlite3_free(zSql);
    if( rc ) return rc;
    nRow = nAlloc = 0;
    azResult = 0;
    if( nArg>1 ){
      sqlite3_bind_text(pStmt, 1, azArg[1], -1, SQLITE_TRANSIENT);
    }else{
      sqlite3_bind_text(pStmt, 1, "%", -1, SQLITE_STATIC);
    }
    while( sqlite3_step(pStmt)==SQLITE_ROW ){
      if( nRow>=nAlloc ){
        char **azNew;
        int n2 = nAlloc*2 + 10;
        azNew = sqlite3_realloc64(azResult, sizeof(azResult[0])*n2);
        if( azNew==0 ){
          fprintf(stderr, "Error: out of memory\n");
          break;
        }
        nAlloc = n2;
        azResult = azNew;
      }
      azResult[nRow] = sqlite3_mprintf("%s", sqlite3_column_text(pStmt, 0));
      if( azResult[nRow] ) nRow++;
    }
    sqlite3_finalize(pStmt);        
    if( nRow>0 ){
      int len, maxlen = 0;
      int i, j;
      int nPrintCol, nPrintRow;
      for(i=0; i<nRow; i++){
        len = strlen30(azResult[i]);
        if( len>maxlen ) maxlen = len;
      }
      nPrintCol = 80/(maxlen+2);
      if( nPrintCol<1 ) nPrintCol = 1;
      nPrintRow = (nRow + nPrintCol - 1)/nPrintCol;
      for(i=0; i<nPrintRow; i++){
        for(j=i; j<nRow; j+=nPrintRow){
          char *zSp = j<nPrintRow ? "" : "  ";
          fprintf(p->out, "%s%-*s", zSp, maxlen, azResult[j] ? azResult[j]:"");
        }
        fprintf(p->out, "\n");
      }
    }
    for(ii=0; ii<nRow; ii++) sqlite3_free(azResult[ii]);
    sqlite3_free(azResult);
  }else

  if( c=='t' && n>=8 && strncmp(azArg[0], "testctrl", n)==0 && nArg>=2 ){
    static const struct {
       const char *zCtrlName;   /* Name of a test-control option */
       int ctrlCode;            /* Integer code for that option */
    } aCtrl[] = {
      { "prng_save",             SQLITE_TESTCTRL_PRNG_SAVE              },
      { "prng_restore",          SQLITE_TESTCTRL_PRNG_RESTORE           },
      { "prng_reset",            SQLITE_TESTCTRL_PRNG_RESET             },
      { "bitvec_test",           SQLITE_TESTCTRL_BITVEC_TEST            },
      { "fault_install",         SQLITE_TESTCTRL_FAULT_INSTALL          },
      { "benign_malloc_hooks",   SQLITE_TESTCTRL_BENIGN_MALLOC_HOOKS    },
      { "pending_byte",          SQLITE_TESTCTRL_PENDING_BYTE           },
      { "assert",                SQLITE_TESTCTRL_ASSERT                 },
      { "always",                SQLITE_TESTCTRL_ALWAYS                 },
      { "reserve",               SQLITE_TESTCTRL_RESERVE                },
      { "optimizations",         SQLITE_TESTCTRL_OPTIMIZATIONS          },
      { "iskeyword",             SQLITE_TESTCTRL_ISKEYWORD              },
      { "scratchmalloc",         SQLITE_TESTCTRL_SCRATCHMALLOC          },
      { "byteorder",             SQLITE_TESTCTRL_BYTEORDER              },
      { "never_corrupt",         SQLITE_TESTCTRL_NEVER_CORRUPT          },
      { "imposter",              SQLITE_TESTCTRL_IMPOSTER               },
    };
    int testctrl = -1;
    int rc2 = 0;
    int i, n2;
    open_db(p, 0);

    /* convert testctrl text option to value. allow any unique prefix
    ** of the option name, or a numerical value. */
    n2 = strlen30(azArg[1]);
    for(i=0; i<(int)(sizeof(aCtrl)/sizeof(aCtrl[0])); i++){
      if( strncmp(azArg[1], aCtrl[i].zCtrlName, n2)==0 ){
        if( testctrl<0 ){
          testctrl = aCtrl[i].ctrlCode;
        }else{
          fprintf(stderr, "ambiguous option name: \"%s\"\n", azArg[1]);
          testctrl = -1;
          break;
        }
      }
    }
    if( testctrl<0 ) testctrl = (int)integerValue(azArg[1]);
    if( (testctrl<SQLITE_TESTCTRL_FIRST) || (testctrl>SQLITE_TESTCTRL_LAST) ){
      fprintf(stderr,"Error: invalid testctrl option: %s\n", azArg[1]);
    }else{
      switch(testctrl){

        /* sqlite3_test_control(int, db, int) */
        case SQLITE_TESTCTRL_OPTIMIZATIONS:
        case SQLITE_TESTCTRL_RESERVE:             
          if( nArg==3 ){
            int opt = (int)strtol(azArg[2], 0, 0);        
            rc2 = sqlite3_test_control(testctrl, p->db, opt);
            fprintf(p->out, "%d (0x%08x)\n", rc2, rc2);
          } else {
            fprintf(stderr,"Error: testctrl %s takes a single int option\n",
                    azArg[1]);
          }
          break;

        /* sqlite3_test_control(int) */
        case SQLITE_TESTCTRL_PRNG_SAVE:
        case SQLITE_TESTCTRL_PRNG_RESTORE:
        case SQLITE_TESTCTRL_PRNG_RESET:
        case SQLITE_TESTCTRL_BYTEORDER:
          if( nArg==2 ){
            rc2 = sqlite3_test_control(testctrl);
            fprintf(p->out, "%d (0x%08x)\n", rc2, rc2);
          } else {
            fprintf(stderr,"Error: testctrl %s takes no options\n", azArg[1]);
          }
          break;

        /* sqlite3_test_control(int, uint) */
        case SQLITE_TESTCTRL_PENDING_BYTE:        
          if( nArg==3 ){
            unsigned int opt = (unsigned int)integerValue(azArg[2]);
            rc2 = sqlite3_test_control(testctrl, opt);
            fprintf(p->out, "%d (0x%08x)\n", rc2, rc2);
          } else {
            fprintf(stderr,"Error: testctrl %s takes a single unsigned"
                           " int option\n", azArg[1]);
          }
          break;
          
        /* sqlite3_test_control(int, int) */
        case SQLITE_TESTCTRL_ASSERT:              
        case SQLITE_TESTCTRL_ALWAYS:      
        case SQLITE_TESTCTRL_NEVER_CORRUPT:        
          if( nArg==3 ){
            int opt = booleanValue(azArg[2]);        
            rc2 = sqlite3_test_control(testctrl, opt);
            fprintf(p->out, "%d (0x%08x)\n", rc2, rc2);
          } else {
            fprintf(stderr,"Error: testctrl %s takes a single int option\n",
                            azArg[1]);
          }
          break;

        /* sqlite3_test_control(int, char *) */
#ifdef SQLITE_N_KEYWORD
        case SQLITE_TESTCTRL_ISKEYWORD:           
          if( nArg==3 ){
            const char *opt = azArg[2];        
            rc2 = sqlite3_test_control(testctrl, opt);
            fprintf(p->out, "%d (0x%08x)\n", rc2, rc2);
          } else {
            fprintf(stderr,"Error: testctrl %s takes a single char * option\n",
                            azArg[1]);
          }
          break;
#endif

        case SQLITE_TESTCTRL_IMPOSTER:
          if( nArg==5 ){
            rc2 = sqlite3_test_control(testctrl, p->db, 
                          azArg[2],
                          integerValue(azArg[3]),
                          integerValue(azArg[4]));
            fprintf(p->out, "%d (0x%08x)\n", rc2, rc2);
          }else{
            fprintf(stderr,"Usage: .testctrl imposter dbName onoff tnum\n");
          }
          break;

        case SQLITE_TESTCTRL_BITVEC_TEST:         
        case SQLITE_TESTCTRL_FAULT_INSTALL:       
        case SQLITE_TESTCTRL_BENIGN_MALLOC_HOOKS: 
        case SQLITE_TESTCTRL_SCRATCHMALLOC:       
        default:
          fprintf(stderr,"Error: CLI support for testctrl %s not implemented\n",
                  azArg[1]);
          break;
      }
    }
  }else

  if( c=='t' && n>4 && strncmp(azArg[0], "timeout", n)==0 ){
    open_db(p, 0);
    sqlite3_busy_timeout(p->db, nArg>=2 ? (int)integerValue(azArg[1]) : 0);
  }else
    
  if( c=='t' && n>=5 && strncmp(azArg[0], "timer", n)==0 ){
    if( nArg==2 ){
      enableTimer = booleanValue(azArg[1]);
      if( enableTimer && !HAS_TIMER ){
        fprintf(stderr, "Error: timer not available on this system.\n");
        enableTimer = 0;
      }
    }else{
      fprintf(stderr, "Usage: .timer on|off\n");
      rc = 1;
    }
  }else
  
  if( c=='t' && strncmp(azArg[0], "trace", n)==0 ){
    open_db(p, 0);
    if( nArg!=2 ){
      fprintf(stderr, "Usage: .trace FILE|off\n");
      rc = 1;
      goto meta_command_exit;
    }
    output_file_close(p->traceOut);
    p->traceOut = output_file_open(azArg[1]);
#if !defined(SQLITE_OMIT_TRACE) && !defined(SQLITE_OMIT_FLOATING_POINT)
    if( p->traceOut==0 ){
      sqlite3_trace(p->db, 0, 0);
    }else{
      sqlite3_trace(p->db, sql_trace_callback, p->traceOut);
    }
#endif
  }else

#if SQLITE_USER_AUTHENTICATION
  if( c=='u' && strncmp(azArg[0], "user", n)==0 ){
    if( nArg<2 ){
      fprintf(stderr, "Usage: .user SUBCOMMAND ...\n");
      rc = 1;
      goto meta_command_exit;
    }
    open_db(p, 0);
    if( strcmp(azArg[1],"login")==0 ){
      if( nArg!=4 ){
        fprintf(stderr, "Usage: .user login USER PASSWORD\n");
        rc = 1;
        goto meta_command_exit;
      }
      rc = sqlite3_user_authenticate(p->db, azArg[2], azArg[3],
                                    (int)strlen(azArg[3]));
      if( rc ){
        fprintf(stderr, "Authentication failed for user %s\n", azArg[2]);
        rc = 1;
      }
    }else if( strcmp(azArg[1],"add")==0 ){
      if( nArg!=5 ){
        fprintf(stderr, "Usage: .user add USER PASSWORD ISADMIN\n");
        rc = 1;
        goto meta_command_exit;
      }
      rc = sqlite3_user_add(p->db, azArg[2],
                            azArg[3], (int)strlen(azArg[3]),
                            booleanValue(azArg[4]));
      if( rc ){
        fprintf(stderr, "User-Add failed: %d\n", rc);
        rc = 1;
      }
    }else if( strcmp(azArg[1],"edit")==0 ){
      if( nArg!=5 ){
        fprintf(stderr, "Usage: .user edit USER PASSWORD ISADMIN\n");
        rc = 1;
        goto meta_command_exit;
      }
      rc = sqlite3_user_change(p->db, azArg[2],
                              azArg[3], (int)strlen(azArg[3]),
                              booleanValue(azArg[4]));
      if( rc ){
        fprintf(stderr, "User-Edit failed: %d\n", rc);
        rc = 1;
      }
    }else if( strcmp(azArg[1],"delete")==0 ){
      if( nArg!=3 ){
        fprintf(stderr, "Usage: .user delete USER\n");
        rc = 1;
        goto meta_command_exit;
      }
      rc = sqlite3_user_delete(p->db, azArg[2]);
      if( rc ){
        fprintf(stderr, "User-Delete failed: %d\n", rc);
        rc = 1;
      }
    }else{
      fprintf(stderr, "Usage: .user login|add|edit|delete ...\n");
      rc = 1;
      goto meta_command_exit;
    }    
  }else
#endif /* SQLITE_USER_AUTHENTICATION */

  if( c=='v' && strncmp(azArg[0], "version", n)==0 ){
    fprintf(p->out, "SQLite %s %s\n" /*extra-version-info*/,
        sqlite3_libversion(), sqlite3_sourceid());
  }else

  if( c=='v' && strncmp(azArg[0], "vfsname", n)==0 ){
    const char *zDbName = nArg==2 ? azArg[1] : "main";
    char *zVfsName = 0;
    if( p->db ){
      sqlite3_file_control(p->db, zDbName, SQLITE_FCNTL_VFSNAME, &zVfsName);
      if( zVfsName ){
        fprintf(p->out, "%s\n", zVfsName);
        sqlite3_free(zVfsName);
      }
    }
  }else

#if defined(SQLITE_DEBUG) && defined(SQLITE_ENABLE_WHERETRACE)
  if( c=='w' && strncmp(azArg[0], "wheretrace", n)==0 ){
    extern int sqlite3WhereTrace;
    sqlite3WhereTrace = nArg>=2 ? booleanValue(azArg[1]) : 0xff;
  }else
#endif

  if( c=='w' && strncmp(azArg[0], "width", n)==0 ){
    int j;
    assert( nArg<=ArraySize(azArg) );
    for(j=1; j<nArg && j<ArraySize(p->colWidth); j++){
      p->colWidth[j-1] = (int)integerValue(azArg[j]);
    }
  }else

  {
    fprintf(stderr, "Error: unknown command or invalid arguments: "
      " \"%s\". Enter \".help\" for help\n", azArg[0]);
    rc = 1;
  }
