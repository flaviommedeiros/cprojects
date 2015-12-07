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
