if ((
#ifdef GUNZIP
                     state->flags ? hold :
#endif
                     REVERSE(hold)) != state->check) {
                    strm->msg = "incorrect data check";
                    state->mode = BAD_DATA;
                    break;
                }
