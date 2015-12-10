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
