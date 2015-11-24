if ((
#ifdef GUNZIP
                              state->flags ? hold :
#endif
                              ZSWAP32(hold)) != state->check) {
                        strm->msg = (char *)"incorrect data check";
                        state->mode = BAD;
                        break;
                     }
