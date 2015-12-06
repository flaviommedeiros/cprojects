if (s->match_length <= 5 && (s->strategy == Z_FILTERED
#if TOO_FAR <= 32767
                  || (s->match_length == MIN_MATCH &&
                     s->strstart - s->match_start > TOO_FAR)
#endif
                  )) {

            /* If prev_match is also MIN_MATCH, match_start is garbage
             * but we will ignore the current match anyway.
             */
            s->match_length = MIN_MATCH-1;
         }
