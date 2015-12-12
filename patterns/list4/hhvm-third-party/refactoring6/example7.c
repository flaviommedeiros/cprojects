if (*previous == OP_CLASS || *previous == OP_NCLASS ||
#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
             *previous == OP_XCLASS ||
#endif
             *previous == OP_REF   || *previous == OP_REFI ||
             *previous == OP_DNREF || *previous == OP_DNREFI)
      {
      if (repeat_max == 0)
        {
        code = previous;
        goto END_REPEAT;
        }

      if (repeat_min == 0 && repeat_max == -1)
        *code++ = OP_CRSTAR + repeat_type;
      else if (repeat_min == 1 && repeat_max == -1)
        *code++ = OP_CRPLUS + repeat_type;
      else if (repeat_min == 0 && repeat_max == 1)
        *code++ = OP_CRQUERY + repeat_type;
      else
        {
        *code++ = OP_CRRANGE + repeat_type;
        PUT2INC(code, 0, repeat_min);
        if (repeat_max == -1) repeat_max = 0;  /* 2-byte encoding for max */
        PUT2INC(code, 0, repeat_max);
        }
      }

    /* If previous was a bracket group, we may have to replicate it in certain
    cases. Note that at this point we can encounter only the "basic" bracket
    opcodes such as BRA and CBRA, as this is the place where they get converted
    into the more special varieties such as BRAPOS and SBRA. A test for >=
    OP_ASSERT and <= OP_COND includes ASSERT, ASSERT_NOT, ASSERTBACK,
    ASSERTBACK_NOT, ONCE, ONCE_NC, BRA, BRAPOS, CBRA, CBRAPOS, and COND.
    Originally, PCRE did not allow repetition of assertions, but now it does,
    for Perl compatibility. */

    else if (*previous >= OP_ASSERT && *previous <= OP_COND)
      {
      register int i;
      int len = (int)(code - previous);
      pcre_uchar *bralink = NULL;
      pcre_uchar *brazeroptr = NULL;

      /* Repeating a DEFINE group is pointless, but Perl allows the syntax, so
      we just ignore the repeat. */

      if (*previous == OP_COND && previous[LINK_SIZE+1] == OP_DEF)
        goto END_REPEAT;

      /* There is no sense in actually repeating assertions. The only potential
      use of repetition is in cases when the assertion is optional. Therefore,
      if the minimum is greater than zero, just ignore the repeat. If the
      maximum is not zero or one, set it to 1. */

      if (*previous < OP_ONCE)    /* Assertion */
        {
        if (repeat_min > 0) goto END_REPEAT;
        if (repeat_max < 0 || repeat_max > 1) repeat_max = 1;
        }

      /* The case of a zero minimum is special because of the need to stick
      OP_BRAZERO in front of it, and because the group appears once in the
      data, whereas in other cases it appears the minimum number of times. For
      this reason, it is simplest to treat this case separately, as otherwise
      the code gets far too messy. There are several special subcases when the
      minimum is zero. */

      if (repeat_min == 0)
        {
        /* If the maximum is also zero, we used to just omit the group from the
        output altogether, like this:

        ** if (repeat_max == 0)
        **   {
        **   code = previous;
        **   goto END_REPEAT;
        **   }

        However, that fails when a group or a subgroup within it is referenced
        as a subroutine from elsewhere in the pattern, so now we stick in
        OP_SKIPZERO in front of it so that it is skipped on execution. As we
        don't have a list of which groups are referenced, we cannot do this
        selectively.

        If the maximum is 1 or unlimited, we just have to stick in the BRAZERO
        and do no more at this point. However, we do need to adjust any
        OP_RECURSE calls inside the group that refer to the group itself or any
        internal or forward referenced group, because the offset is from the
        start of the whole regex. Temporarily terminate the pattern while doing
        this. */

        if (repeat_max <= 1)    /* Covers 0, 1, and unlimited */
          {
          *code = OP_END;
          adjust_recurse(previous, 1, utf, cd, save_hwm);
          memmove(previous + 1, previous, IN_UCHARS(len));
          code++;
          if (repeat_max == 0)
            {
            *previous++ = OP_SKIPZERO;
            goto END_REPEAT;
            }
          brazeroptr = previous;    /* Save for possessive optimizing */
          *previous++ = OP_BRAZERO + repeat_type;
          }

        /* If the maximum is greater than 1 and limited, we have to replicate
        in a nested fashion, sticking OP_BRAZERO before each set of brackets.
        The first one has to be handled carefully because it's the original
        copy, which has to be moved up. The remainder can be handled by code
        that is common with the non-zero minimum case below. We have to
        adjust the value or repeat_max, since one less copy is required. Once
        again, we may have to adjust any OP_RECURSE calls inside the group. */

        else
          {
          int offset;
          *code = OP_END;
          adjust_recurse(previous, 2 + LINK_SIZE, utf, cd, save_hwm);
          memmove(previous + 2 + LINK_SIZE, previous, IN_UCHARS(len));
          code += 2 + LINK_SIZE;
          *previous++ = OP_BRAZERO + repeat_type;
          *previous++ = OP_BRA;

          /* We chain together the bracket offset fields that have to be
          filled in later when the ends of the brackets are reached. */

          offset = (bralink == NULL)? 0 : (int)(previous - bralink);
          bralink = previous;
          PUTINC(previous, 0, offset);
          }

        repeat_max--;
        }

      /* If the minimum is greater than zero, replicate the group as many
      times as necessary, and adjust the maximum to the number of subsequent
      copies that we need. If we set a first char from the group, and didn't
      set a required char, copy the latter from the former. If there are any
      forward reference subroutine calls in the group, there will be entries on
      the workspace list; replicate these with an appropriate increment. */

      else
        {
        if (repeat_min > 1)
          {
          /* In the pre-compile phase, we don't actually do the replication. We
          just adjust the length as if we had. Do some paranoid checks for
          potential integer overflow. The INT64_OR_DOUBLE type is a 64-bit
          integer type when available, otherwise double. */

          if (lengthptr != NULL)
            {
            int delta = (repeat_min - 1)*length_prevgroup;
            if ((INT64_OR_DOUBLE)(repeat_min - 1)*
                  (INT64_OR_DOUBLE)length_prevgroup >
                    (INT64_OR_DOUBLE)INT_MAX ||
                OFLOW_MAX - *lengthptr < delta)
              {
              *errorcodeptr = ERR20;
              goto FAILED;
              }
            *lengthptr += delta;
            }

          /* This is compiling for real. If there is a set first byte for
          the group, and we have not yet set a "required byte", set it. Make
          sure there is enough workspace for copying forward references before
          doing the copy. */

          else
            {
            if (groupsetfirstchar && reqcharflags < 0)
              {
              reqchar = firstchar;
              reqcharflags = firstcharflags;
              }

            for (i = 1; i < repeat_min; i++)
              {
              pcre_uchar *hc;
              pcre_uchar *this_hwm = cd->hwm;
              memcpy(code, previous, IN_UCHARS(len));

              while (cd->hwm > cd->start_workspace + cd->workspace_size -
                     WORK_SIZE_SAFETY_MARGIN - (this_hwm - save_hwm))
                {
                size_t save_offset = save_hwm - cd->start_workspace;
                size_t this_offset = this_hwm - cd->start_workspace;
                *errorcodeptr = expand_workspace(cd);
                if (*errorcodeptr != 0) goto FAILED;
                save_hwm = (pcre_uchar *)cd->start_workspace + save_offset;
                this_hwm = (pcre_uchar *)cd->start_workspace + this_offset;
                }

              for (hc = save_hwm; hc < this_hwm; hc += LINK_SIZE)
                {
                PUT(cd->hwm, 0, GET(hc, 0) + len);
                cd->hwm += LINK_SIZE;
                }
              save_hwm = this_hwm;
              code += len;
              }
            }
          }

        if (repeat_max > 0) repeat_max -= repeat_min;
        }

      /* This code is common to both the zero and non-zero minimum cases. If
      the maximum is limited, it replicates the group in a nested fashion,
      remembering the bracket starts on a stack. In the case of a zero minimum,
      the first one was set up above. In all cases the repeat_max now specifies
      the number of additional copies needed. Again, we must remember to
      replicate entries on the forward reference list. */

      if (repeat_max >= 0)
        {
        /* In the pre-compile phase, we don't actually do the replication. We
        just adjust the length as if we had. For each repetition we must add 1
        to the length for BRAZERO and for all but the last repetition we must
        add 2 + 2*LINKSIZE to allow for the nesting that occurs. Do some
        paranoid checks to avoid integer overflow. The INT64_OR_DOUBLE type is
        a 64-bit integer type when available, otherwise double. */

        if (lengthptr != NULL && repeat_max > 0)
          {
          int delta = repeat_max * (length_prevgroup + 1 + 2 + 2*LINK_SIZE) -
                      2 - 2*LINK_SIZE;   /* Last one doesn't nest */
          if ((INT64_OR_DOUBLE)repeat_max *
                (INT64_OR_DOUBLE)(length_prevgroup + 1 + 2 + 2*LINK_SIZE)
                  > (INT64_OR_DOUBLE)INT_MAX ||
              OFLOW_MAX - *lengthptr < delta)
            {
            *errorcodeptr = ERR20;
            goto FAILED;
            }
          *lengthptr += delta;
          }

        /* This is compiling for real */

        else for (i = repeat_max - 1; i >= 0; i--)
          {
          pcre_uchar *hc;
          pcre_uchar *this_hwm = cd->hwm;

          *code++ = OP_BRAZERO + repeat_type;

          /* All but the final copy start a new nesting, maintaining the
          chain of brackets outstanding. */

          if (i != 0)
            {
            int offset;
            *code++ = OP_BRA;
            offset = (bralink == NULL)? 0 : (int)(code - bralink);
            bralink = code;
            PUTINC(code, 0, offset);
            }

          memcpy(code, previous, IN_UCHARS(len));

          /* Ensure there is enough workspace for forward references before
          copying them. */

          while (cd->hwm > cd->start_workspace + cd->workspace_size -
                 WORK_SIZE_SAFETY_MARGIN - (this_hwm - save_hwm))
            {
            size_t save_offset = save_hwm - cd->start_workspace;
            size_t this_offset = this_hwm - cd->start_workspace;
            *errorcodeptr = expand_workspace(cd);
            if (*errorcodeptr != 0) goto FAILED;
            save_hwm = (pcre_uchar *)cd->start_workspace + save_offset;
            this_hwm = (pcre_uchar *)cd->start_workspace + this_offset;
            }

          for (hc = save_hwm; hc < this_hwm; hc += LINK_SIZE)
            {
            PUT(cd->hwm, 0, GET(hc, 0) + len + ((i != 0)? 2+LINK_SIZE : 1));
            cd->hwm += LINK_SIZE;
            }
          save_hwm = this_hwm;
          code += len;
          }

        /* Now chain through the pending brackets, and fill in their length
        fields (which are holding the chain links pro tem). */

        while (bralink != NULL)
          {
          int oldlinkoffset;
          int offset = (int)(code - bralink + 1);
          pcre_uchar *bra = code - offset;
          oldlinkoffset = GET(bra, 1);
          bralink = (oldlinkoffset == 0)? NULL : bralink - oldlinkoffset;
          *code++ = OP_KET;
          PUTINC(code, 0, offset);
          PUT(bra, 1, offset);
          }
        }

      /* If the maximum is unlimited, set a repeater in the final copy. For
      ONCE brackets, that's all we need to do. However, possessively repeated
      ONCE brackets can be converted into non-capturing brackets, as the
      behaviour of (?:xx)++ is the same as (?>xx)++ and this saves having to
      deal with possessive ONCEs specially.

      Otherwise, when we are doing the actual compile phase, check to see
      whether this group is one that could match an empty string. If so,
      convert the initial operator to the S form (e.g. OP_BRA -> OP_SBRA) so
      that runtime checking can be done. [This check is also applied to ONCE
      groups at runtime, but in a different way.]

      Then, if the quantifier was possessive and the bracket is not a
      conditional, we convert the BRA code to the POS form, and the KET code to
      KETRPOS. (It turns out to be convenient at runtime to detect this kind of
      subpattern at both the start and at the end.) The use of special opcodes
      makes it possible to reduce greatly the stack usage in pcre_exec(). If
      the group is preceded by OP_BRAZERO, convert this to OP_BRAPOSZERO.

      Then, if the minimum number of matches is 1 or 0, cancel the possessive
      flag so that the default action below, of wrapping everything inside
      atomic brackets, does not happen. When the minimum is greater than 1,
      there will be earlier copies of the group, and so we still have to wrap
      the whole thing. */

      else
        {
        pcre_uchar *ketcode = code - 1 - LINK_SIZE;
        pcre_uchar *bracode = ketcode - GET(ketcode, 1);

        /* Convert possessive ONCE brackets to non-capturing */

        if ((*bracode == OP_ONCE || *bracode == OP_ONCE_NC) &&
            possessive_quantifier) *bracode = OP_BRA;

        /* For non-possessive ONCE brackets, all we need to do is to
        set the KET. */

        if (*bracode == OP_ONCE || *bracode == OP_ONCE_NC)
          *ketcode = OP_KETRMAX + repeat_type;

        /* Handle non-ONCE brackets and possessive ONCEs (which have been
        converted to non-capturing above). */

        else
          {
          /* In the compile phase, check for empty string matching. */

          if (lengthptr == NULL)
            {
            pcre_uchar *scode = bracode;
            do
              {
              if (could_be_empty_branch(scode, ketcode, utf, cd, NULL))
                {
                *bracode += OP_SBRA - OP_BRA;
                break;
                }
              scode += GET(scode, 1);
              }
            while (*scode == OP_ALT);
            }

          /* Handle possessive quantifiers. */

          if (possessive_quantifier)
            {
            /* For COND brackets, we wrap the whole thing in a possessively
            repeated non-capturing bracket, because we have not invented POS
            versions of the COND opcodes. Because we are moving code along, we
            must ensure that any pending recursive references are updated. */

            if (*bracode == OP_COND || *bracode == OP_SCOND)
              {
              int nlen = (int)(code - bracode);
              *code = OP_END;
              adjust_recurse(bracode, 1 + LINK_SIZE, utf, cd, save_hwm);
              memmove(bracode + 1 + LINK_SIZE, bracode, IN_UCHARS(nlen));
              code += 1 + LINK_SIZE;
              nlen += 1 + LINK_SIZE;
              *bracode = OP_BRAPOS;
              *code++ = OP_KETRPOS;
              PUTINC(code, 0, nlen);
              PUT(bracode, 1, nlen);
              }

            /* For non-COND brackets, we modify the BRA code and use KETRPOS. */

            else
              {
              *bracode += 1;              /* Switch to xxxPOS opcodes */
              *ketcode = OP_KETRPOS;
              }

            /* If the minimum is zero, mark it as possessive, then unset the
            possessive flag when the minimum is 0 or 1. */

            if (brazeroptr != NULL) *brazeroptr = OP_BRAPOSZERO;
            if (repeat_min < 2) possessive_quantifier = FALSE;
            }

          /* Non-possessive quantifier */

          else *ketcode = OP_KETRMAX + repeat_type;
          }
        }
      }

    /* If previous is OP_FAIL, it was generated by an empty class [] in
    JavaScript mode. The other ways in which OP_FAIL can be generated, that is
    by (*FAIL) or (?!) set previous to NULL, which gives a "nothing to repeat"
    error above. We can just ignore the repeat in JS case. */

    else if (*previous == OP_FAIL) goto END_REPEAT;

    /* Else there's some kind of shambles */

    else
      {
      *errorcodeptr = ERR11;
      goto FAILED;
      }
