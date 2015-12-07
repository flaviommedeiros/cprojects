if ((re_opcode_t) *p2 == exactn
#ifdef MBS_SUPPORT
		     || (re_opcode_t) *p2 == exactn_bin
#endif
		     || (bufp->newline_anchor && (re_opcode_t) *p2 == endline))
	      {
		register UCHAR_T c
                  = *p2 == (UCHAR_T) endline ? '\n' : p2[2];

                if (((re_opcode_t) p1[1+OFFSET_ADDRESS_SIZE] == exactn
#ifdef MBS_SUPPORT
		     || (re_opcode_t) p1[1+OFFSET_ADDRESS_SIZE] == exactn_bin
#endif
		    ) && p1[3+OFFSET_ADDRESS_SIZE] != c)
                  {
  		    p[-(1+OFFSET_ADDRESS_SIZE)] = (UCHAR_T)
		      pop_failure_jump;
#ifdef WCHAR
		      DEBUG_PRINT3 ("  %C != %C => pop_failure_jump.\n",
				    (wint_t) c,
				    (wint_t) p1[3+OFFSET_ADDRESS_SIZE]);
#else
		      DEBUG_PRINT3 ("  %c != %c => pop_failure_jump.\n",
				    (char) c,
				    (char) p1[3+OFFSET_ADDRESS_SIZE]);
#endif
                  }

#ifndef WCHAR
		else if ((re_opcode_t) p1[3] == charset
			 || (re_opcode_t) p1[3] == charset_not)
		  {
		    int negate = (re_opcode_t) p1[3] == charset_not;

		    if (c < (unsigned) (p1[4] * BYTEWIDTH)
			&& p1[5 + c / BYTEWIDTH] & (1 << (c % BYTEWIDTH)))
		      negate = !negate;

                    /* `negate' is equal to 1 if c would match, which means
                        that we can't change to pop_failure_jump.  */
		    if (!negate)
                      {
  		        p[-3] = (unsigned char) pop_failure_jump;
                        DEBUG_PRINT1 ("  No match => pop_failure_jump.\n");
                      }
		  }
#endif /* not WCHAR */
	      }
#ifndef WCHAR
            else if ((re_opcode_t) *p2 == charset)
	      {
		/* We win if the first character of the loop is not part
                   of the charset.  */
                if ((re_opcode_t) p1[3] == exactn
 		    && ! ((int) p2[1] * BYTEWIDTH > (int) p1[5]
 			  && (p2[2 + p1[5] / BYTEWIDTH]
 			      & (1 << (p1[5] % BYTEWIDTH)))))
		  {
		    p[-3] = (unsigned char) pop_failure_jump;
		    DEBUG_PRINT1 ("  No match => pop_failure_jump.\n");
                  }

		else if ((re_opcode_t) p1[3] == charset_not)
		  {
		    int idx;
		    /* We win if the charset_not inside the loop
		       lists every character listed in the charset after.  */
		    for (idx = 0; idx < (int) p2[1]; idx++)
		      if (! (p2[2 + idx] == 0
			     || (idx < (int) p1[4]
				 && ((p2[2 + idx] & ~ p1[5 + idx]) == 0))))
			break;

		    if (idx == p2[1])
                      {
  		        p[-3] = (unsigned char) pop_failure_jump;
                        DEBUG_PRINT1 ("  No match => pop_failure_jump.\n");
                      }
		  }
		else if ((re_opcode_t) p1[3] == charset)
		  {
		    int idx;
		    /* We win if the charset inside the loop
		       has no overlap with the one after the loop.  */
		    for (idx = 0;
			 idx < (int) p2[1] && idx < (int) p1[4];
			 idx++)
		      if ((p2[2 + idx] & p1[5 + idx]) != 0)
			break;

		    if (idx == p2[1] || idx == p1[4])
                      {
  		        p[-3] = (unsigned char) pop_failure_jump;
                        DEBUG_PRINT1 ("  No match => pop_failure_jump.\n");
                      }
		  }
	      }
