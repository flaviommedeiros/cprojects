if ((
#ifdef GUNZIP
                     state->flags ? hold :
#endif
                     REVERSE(hold)) != state->check) {
                    strm->msg = __UNCONST("incorrect data check");
                    state->mode = BAD;
                    break;
                }
