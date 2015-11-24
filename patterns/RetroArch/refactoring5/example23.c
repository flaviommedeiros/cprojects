#ifndef FASTEST
if (s->match_length <= s->max_insert_length &&
               s->lookahead >= MIN_MATCH) {
            s->match_length--; /* string at strstart already in table */
            do {
               s->strstart++;
               INSERT_STRING(s, s->strstart, hash_head);
               /* strstart never exceeds WSIZE-MAX_MATCH, so there are
                * always MIN_MATCH bytes ahead.
                */
            } while (--s->match_length != 0);
            s->strstart++;
         } else
#endif
         {
            s->strstart += s->match_length;
            s->match_length = 0;
            s->ins_h = s->window[s->strstart];
            UPDATE_HASH(s, s->ins_h, s->window[s->strstart+1]);
#if MIN_MATCH != 3
            Call UPDATE_HASH() MIN_MATCH-3 more times
#endif
               /* If lookahead < MIN_MATCH, ins_h is garbage, but it does not
                * matter since it will be recomputed at next deflate call.
                */
         }
