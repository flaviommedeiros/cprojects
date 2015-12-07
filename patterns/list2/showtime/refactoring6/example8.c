if( 
#if fts5YY_SHIFT_MIN+fts5YYWILDCARD<0
          j>=0 &&
#endif
#if fts5YY_SHIFT_MAX+fts5YYWILDCARD>=fts5YY_ACTTAB_COUNT
          j<fts5YY_ACTTAB_COUNT &&
#endif
          fts5yy_lookahead[j]==fts5YYWILDCARD
        ){
#ifndef NDEBUG
          if( fts5yyTraceFILE ){
            fprintf(fts5yyTraceFILE, "%sWILDCARD %s => %s\n",
               fts5yyTracePrompt, fts5yyTokenName[iLookAhead], fts5yyTokenName[fts5YYWILDCARD]);
          }
#endif /* NDEBUG */
          return fts5yy_action[j];
        }
