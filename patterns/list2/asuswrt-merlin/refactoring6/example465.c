if (!pending_exact
#ifdef WCHAR
	      /* If last exactn handle binary(or character) and
		 new exactn handle character(or binary).  */
	      || is_exactn_bin != is_binary[p - 1 - pattern]
#endif /* WCHAR */

              /* If last exactn not at current position.  */
              || pending_exact + *pending_exact + 1 != b

              /* We have only one byte following the exactn for the count.  */
	      || *pending_exact == (1 << BYTEWIDTH) - 1

              /* If followed by a repetition operator.  */
              || *p == '*' || *p == '^'
	      || ((syntax & RE_BK_PLUS_QM)
		  ? *p == '\\' && (p[1] == '+' || p[1] == '?')
		  : (*p == '+' || *p == '?'))
	      || ((syntax & RE_INTERVALS)
                  && ((syntax & RE_NO_BK_BRACES)
		      ? *p == '{'
                      : (p[0] == '\\' && p[1] == '{'))))
	    {
	      /* Start building a new exactn.  */

              laststart = b;

#ifdef WCHAR
	      /* Is this exactn binary data or character? */
	      is_exactn_bin = is_binary[p - 1 - pattern];
	      if (is_exactn_bin)
		  BUF_PUSH_2 (exactn_bin, 0);
	      else
		  BUF_PUSH_2 (exactn, 0);
#else
	      BUF_PUSH_2 (exactn, 0);
#endif /* WCHAR */
	      pending_exact = b - 1;
            }
