switch (codevalue)
      {
/* ========================================================================== */
      /* These cases are never obeyed. This is a fudge that causes a compile-
      time error if the vectors coptable or poptable, which are indexed by
      opcode, are not the correct length. It seems to be the only way to do
      such a check at compile time, as the sizeof() operator does not work
      in the C preprocessor. */

      case OP_TABLE_LENGTH:
      case OP_TABLE_LENGTH +
        ((sizeof(coptable) == OP_TABLE_LENGTH) &&
         (sizeof(poptable) == OP_TABLE_LENGTH)):
      break;

/* ========================================================================== */
      /* Reached a closing bracket. If not at the end of the pattern, carry
      on with the next opcode. For repeating opcodes, also add the repeat
      state. Note that KETRPOS will always be encountered at the end of the
      subpattern, because the possessive subpattern repeats are always handled
      using recursive calls. Thus, it never adds any new states.

      At the end of the (sub)pattern, unless we have an empty string and
      PCRE_NOTEMPTY is set, or PCRE_NOTEMPTY_ATSTART is set and we are at the
      start of the subject, save the match data, shifting up all previous
      matches so we always have the longest first. */

      case OP_KET:
      case OP_KETRMIN:
      case OP_KETRMAX:
      case OP_KETRPOS:
      if (code != end_code)
        {
        ADD_ACTIVE(state_offset + 1 + LINK_SIZE, 0);
        if (codevalue != OP_KET)
          {
          ADD_ACTIVE(state_offset - GET(code, 1), 0);
          }
        }
      else
        {
        if (ptr > current_subject ||
            ((md->moptions & PCRE_NOTEMPTY) == 0 &&
              ((md->moptions & PCRE_NOTEMPTY_ATSTART) == 0 ||
                current_subject > start_subject + md->start_offset)))
          {
          if (match_count < 0) match_count = (offsetcount >= 2)? 1 : 0;
            else if (match_count > 0 && ++match_count * 2 > offsetcount)
              match_count = 0;
          count = ((match_count == 0)? offsetcount : match_count * 2) - 2;
          if (count > 0) memmove(offsets + 2, offsets, count * sizeof(int));
          if (offsetcount >= 2)
            {
            offsets[0] = (int)(current_subject - start_subject);
            offsets[1] = (int)(ptr - start_subject);
            DPRINTF(("%.*sSet matched string = \"%.*s\"\n", rlevel*2-2, SP,
              offsets[1] - offsets[0], (char *)current_subject));
            }
          if ((md->moptions & PCRE_DFA_SHORTEST) != 0)
            {
            DPRINTF(("%.*sEnd of internal_dfa_exec %d: returning %d\n"
              "%.*s---------------------\n\n", rlevel*2-2, SP, rlevel,
              match_count, rlevel*2-2, SP));
            return match_count;
            }
          }
        }
      break;

/* ========================================================================== */
      /* These opcodes add to the current list of states without looking
      at the current character. */

      /*-----------------------------------------------------------------*/
      case OP_ALT:
      do { code += GET(code, 1); } while (*code == OP_ALT);
      ADD_ACTIVE((int)(code - start_code), 0);
      break;

      /*-----------------------------------------------------------------*/
      case OP_BRA:
      case OP_SBRA:
      do
        {
        ADD_ACTIVE((int)(code - start_code + 1 + LINK_SIZE), 0);
        code += GET(code, 1);
        }
      while (*code == OP_ALT);
      break;

      /*-----------------------------------------------------------------*/
      case OP_CBRA:
      case OP_SCBRA:
      ADD_ACTIVE((int)(code - start_code + 1 + LINK_SIZE + IMM2_SIZE),  0);
      code += GET(code, 1);
      while (*code == OP_ALT)
        {
        ADD_ACTIVE((int)(code - start_code + 1 + LINK_SIZE),  0);
        code += GET(code, 1);
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_BRAZERO:
      case OP_BRAMINZERO:
      ADD_ACTIVE(state_offset + 1, 0);
      code += 1 + GET(code, 2);
      while (*code == OP_ALT) code += GET(code, 1);
      ADD_ACTIVE((int)(code - start_code + 1 + LINK_SIZE), 0);
      break;

      /*-----------------------------------------------------------------*/
      case OP_SKIPZERO:
      code += 1 + GET(code, 2);
      while (*code == OP_ALT) code += GET(code, 1);
      ADD_ACTIVE((int)(code - start_code + 1 + LINK_SIZE), 0);
      break;

      /*-----------------------------------------------------------------*/
      case OP_CIRC:
      if (ptr == start_subject && (md->moptions & PCRE_NOTBOL) == 0)
        { ADD_ACTIVE(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_CIRCM:
      if ((ptr == start_subject && (md->moptions & PCRE_NOTBOL) == 0) ||
          (ptr != end_subject && WAS_NEWLINE(ptr)))
        { ADD_ACTIVE(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_EOD:
      if (ptr >= end_subject)
        {
        if ((md->moptions & PCRE_PARTIAL_HARD) != 0)
          could_continue = TRUE;
        else { ADD_ACTIVE(state_offset + 1, 0); }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_SOD:
      if (ptr == start_subject) { ADD_ACTIVE(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_SOM:
      if (ptr == start_subject + start_offset) { ADD_ACTIVE(state_offset + 1, 0); }
      break;


/* ========================================================================== */
      /* These opcodes inspect the next subject character, and sometimes
      the previous one as well, but do not have an argument. The variable
      clen contains the length of the current character and is zero if we are
      at the end of the subject. */

      /*-----------------------------------------------------------------*/
      case OP_ANY:
      if (clen > 0 && !IS_NEWLINE(ptr))
        {
        if (ptr + 1 >= md->end_subject &&
            (md->moptions & (PCRE_PARTIAL_HARD)) != 0 &&
            NLBLOCK->nltype == NLTYPE_FIXED &&
            NLBLOCK->nllen == 2 &&
            c == NLBLOCK->nl[0])
          {
          could_continue = partial_newline = TRUE;
          }
        else
          {
          ADD_NEW(state_offset + 1, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_ALLANY:
      if (clen > 0)
        { ADD_NEW(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_EODN:
      if (clen == 0 && (md->moptions & PCRE_PARTIAL_HARD) != 0)
        could_continue = TRUE;
      else if (clen == 0 || (IS_NEWLINE(ptr) && ptr == end_subject - md->nllen))
        { ADD_ACTIVE(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_DOLL:
      if ((md->moptions & PCRE_NOTEOL) == 0)
        {
        if (clen == 0 && (md->moptions & PCRE_PARTIAL_HARD) != 0)
          could_continue = TRUE;
        else if (clen == 0 ||
            ((md->poptions & PCRE_DOLLAR_ENDONLY) == 0 && IS_NEWLINE(ptr) &&
               (ptr == end_subject - md->nllen)
            ))
          { ADD_ACTIVE(state_offset + 1, 0); }
        else if (ptr + 1 >= md->end_subject &&
                 (md->moptions & (PCRE_PARTIAL_HARD|PCRE_PARTIAL_SOFT)) != 0 &&
                 NLBLOCK->nltype == NLTYPE_FIXED &&
                 NLBLOCK->nllen == 2 &&
                 c == NLBLOCK->nl[0])
          {
          if ((md->moptions & PCRE_PARTIAL_HARD) != 0)
            {
            reset_could_continue = TRUE;
            ADD_NEW_DATA(-(state_offset + 1), 0, 1);
            }
          else could_continue = partial_newline = TRUE;
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_DOLLM:
      if ((md->moptions & PCRE_NOTEOL) == 0)
        {
        if (clen == 0 && (md->moptions & PCRE_PARTIAL_HARD) != 0)
          could_continue = TRUE;
        else if (clen == 0 ||
            ((md->poptions & PCRE_DOLLAR_ENDONLY) == 0 && IS_NEWLINE(ptr)))
          { ADD_ACTIVE(state_offset + 1, 0); }
        else if (ptr + 1 >= md->end_subject &&
                 (md->moptions & (PCRE_PARTIAL_HARD|PCRE_PARTIAL_SOFT)) != 0 &&
                 NLBLOCK->nltype == NLTYPE_FIXED &&
                 NLBLOCK->nllen == 2 &&
                 c == NLBLOCK->nl[0])
          {
          if ((md->moptions & PCRE_PARTIAL_HARD) != 0)
            {
            reset_could_continue = TRUE;
            ADD_NEW_DATA(-(state_offset + 1), 0, 1);
            }
          else could_continue = partial_newline = TRUE;
          }
        }
      else if (IS_NEWLINE(ptr))
        { ADD_ACTIVE(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/

      case OP_DIGIT:
      case OP_WHITESPACE:
      case OP_WORDCHAR:
      if (clen > 0 && c < 256 &&
            ((ctypes[c] & toptable1[codevalue]) ^ toptable2[codevalue]) != 0)
        { ADD_NEW(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_NOT_DIGIT:
      case OP_NOT_WHITESPACE:
      case OP_NOT_WORDCHAR:
      if (clen > 0 && (c >= 256 ||
            ((ctypes[c] & toptable1[codevalue]) ^ toptable2[codevalue]) != 0))
        { ADD_NEW(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_WORD_BOUNDARY:
      case OP_NOT_WORD_BOUNDARY:
        {
        int left_word, right_word;

        if (ptr > start_subject)
          {
          const pcre_uchar *temp = ptr - 1;
          if (temp < md->start_used_ptr) md->start_used_ptr = temp;
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
          if (utf) { BACKCHAR(temp); }
#endif
          GETCHARTEST(d, temp);
#ifdef SUPPORT_UCP
          if ((md->poptions & PCRE_UCP) != 0)
            {
            if (d == '_') left_word = TRUE; else
              {
              int cat = UCD_CATEGORY(d);
              left_word = (cat == ucp_L || cat == ucp_N);
              }
            }
          else
#endif
          left_word = d < 256 && (ctypes[d] & ctype_word) != 0;
          }
        else left_word = FALSE;

        if (clen > 0)
          {
#ifdef SUPPORT_UCP
          if ((md->poptions & PCRE_UCP) != 0)
            {
            if (c == '_') right_word = TRUE; else
              {
              int cat = UCD_CATEGORY(c);
              right_word = (cat == ucp_L || cat == ucp_N);
              }
            }
          else
#endif
          right_word = c < 256 && (ctypes[c] & ctype_word) != 0;
          }
        else right_word = FALSE;

        if ((left_word == right_word) == (codevalue == OP_NOT_WORD_BOUNDARY))
          { ADD_ACTIVE(state_offset + 1, 0); }
        }
      break;


      /*-----------------------------------------------------------------*/
      /* Check the next character by Unicode property. We will get here only
      if the support is in the binary; otherwise a compile-time error occurs.
      */

#ifdef SUPPORT_UCP
      case OP_PROP:
      case OP_NOTPROP:
      if (clen > 0)
        {
        BOOL OK;
        const pcre_uint32 *cp;
        const ucd_record * prop = GET_UCD(c);
        switch(code[1])
          {
          case PT_ANY:
          OK = TRUE;
          break;

          case PT_LAMP:
          OK = prop->chartype == ucp_Lu || prop->chartype == ucp_Ll ||
               prop->chartype == ucp_Lt;
          break;

          case PT_GC:
          OK = PRIV(ucp_gentype)[prop->chartype] == code[2];
          break;

          case PT_PC:
          OK = prop->chartype == code[2];
          break;

          case PT_SC:
          OK = prop->script == code[2];
          break;

          /* These are specials for combination cases. */

          case PT_ALNUM:
          OK = PRIV(ucp_gentype)[prop->chartype] == ucp_L ||
               PRIV(ucp_gentype)[prop->chartype] == ucp_N;
          break;

          /* Perl space used to exclude VT, but from Perl 5.18 it is included,
          which means that Perl space and POSIX space are now identical. PCRE
          was changed at release 8.34. */

          case PT_SPACE:    /* Perl space */
          case PT_PXSPACE:  /* POSIX space */
          switch(c)
            {
            HSPACE_CASES:
            VSPACE_CASES:
            OK = TRUE;
            break;

            default:
            OK = PRIV(ucp_gentype)[prop->chartype] == ucp_Z;
            break;
            }
          break;

          case PT_WORD:
          OK = PRIV(ucp_gentype)[prop->chartype] == ucp_L ||
               PRIV(ucp_gentype)[prop->chartype] == ucp_N ||
               c == CHAR_UNDERSCORE;
          break;

          case PT_CLIST:
          cp = PRIV(ucd_caseless_sets) + code[2];
          for (;;)
            {
            if (c < *cp) { OK = FALSE; break; }
            if (c == *cp++) { OK = TRUE; break; }
            }
          break;

          case PT_UCNC:
          OK = c == CHAR_DOLLAR_SIGN || c == CHAR_COMMERCIAL_AT ||
               c == CHAR_GRAVE_ACCENT || (c >= 0xa0 && c <= 0xd7ff) ||
               c >= 0xe000;
          break;

          /* Should never occur, but keep compilers from grumbling. */

          default:
          OK = codevalue != OP_PROP;
          break;
          }

        if (OK == (codevalue == OP_PROP)) { ADD_NEW(state_offset + 3, 0); }
        }
      break;
#endif



/* ========================================================================== */
      /* These opcodes likewise inspect the subject character, but have an
      argument that is not a data character. It is one of these opcodes:
      OP_ANY, OP_ALLANY, OP_DIGIT, OP_NOT_DIGIT, OP_WHITESPACE, OP_NOT_SPACE,
      OP_WORDCHAR, OP_NOT_WORDCHAR. The value is loaded into d. */

      case OP_TYPEPLUS:
      case OP_TYPEMINPLUS:
      case OP_TYPEPOSPLUS:
      count = current_state->count;  /* Already matched */
      if (count > 0) { ADD_ACTIVE(state_offset + 2, 0); }
      if (clen > 0)
        {
        if (d == OP_ANY && ptr + 1 >= md->end_subject &&
            (md->moptions & (PCRE_PARTIAL_HARD)) != 0 &&
            NLBLOCK->nltype == NLTYPE_FIXED &&
            NLBLOCK->nllen == 2 &&
            c == NLBLOCK->nl[0])
          {
          could_continue = partial_newline = TRUE;
          }
        else if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
            (c < 256 &&
              (d != OP_ANY || !IS_NEWLINE(ptr)) &&
              ((ctypes[c] & toptable1[d]) ^ toptable2[d]) != 0))
          {
          if (count > 0 && codevalue == OP_TYPEPOSPLUS)
            {
            active_count--;            /* Remove non-match possibility */
            next_active_state--;
            }
          count++;
          ADD_NEW(state_offset, count);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_TYPEQUERY:
      case OP_TYPEMINQUERY:
      case OP_TYPEPOSQUERY:
      ADD_ACTIVE(state_offset + 2, 0);
      if (clen > 0)
        {
        if (d == OP_ANY && ptr + 1 >= md->end_subject &&
            (md->moptions & (PCRE_PARTIAL_HARD)) != 0 &&
            NLBLOCK->nltype == NLTYPE_FIXED &&
            NLBLOCK->nllen == 2 &&
            c == NLBLOCK->nl[0])
          {
          could_continue = partial_newline = TRUE;
          }
        else if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
            (c < 256 &&
              (d != OP_ANY || !IS_NEWLINE(ptr)) &&
              ((ctypes[c] & toptable1[d]) ^ toptable2[d]) != 0))
          {
          if (codevalue == OP_TYPEPOSQUERY)
            {
            active_count--;            /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW(state_offset + 2, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_TYPESTAR:
      case OP_TYPEMINSTAR:
      case OP_TYPEPOSSTAR:
      ADD_ACTIVE(state_offset + 2, 0);
      if (clen > 0)
        {
        if (d == OP_ANY && ptr + 1 >= md->end_subject &&
            (md->moptions & (PCRE_PARTIAL_HARD)) != 0 &&
            NLBLOCK->nltype == NLTYPE_FIXED &&
            NLBLOCK->nllen == 2 &&
            c == NLBLOCK->nl[0])
          {
          could_continue = partial_newline = TRUE;
          }
        else if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
            (c < 256 &&
              (d != OP_ANY || !IS_NEWLINE(ptr)) &&
              ((ctypes[c] & toptable1[d]) ^ toptable2[d]) != 0))
          {
          if (codevalue == OP_TYPEPOSSTAR)
            {
            active_count--;            /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW(state_offset, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_TYPEEXACT:
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        if (d == OP_ANY && ptr + 1 >= md->end_subject &&
            (md->moptions & (PCRE_PARTIAL_HARD)) != 0 &&
            NLBLOCK->nltype == NLTYPE_FIXED &&
            NLBLOCK->nllen == 2 &&
            c == NLBLOCK->nl[0])
          {
          could_continue = partial_newline = TRUE;
          }
        else if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
            (c < 256 &&
              (d != OP_ANY || !IS_NEWLINE(ptr)) &&
              ((ctypes[c] & toptable1[d]) ^ toptable2[d]) != 0))
          {
          if (++count >= (int)GET2(code, 1))
            { ADD_NEW(state_offset + 1 + IMM2_SIZE + 1, 0); }
          else
            { ADD_NEW(state_offset, count); }
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_TYPEUPTO:
      case OP_TYPEMINUPTO:
      case OP_TYPEPOSUPTO:
      ADD_ACTIVE(state_offset + 2 + IMM2_SIZE, 0);
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        if (d == OP_ANY && ptr + 1 >= md->end_subject &&
            (md->moptions & (PCRE_PARTIAL_HARD)) != 0 &&
            NLBLOCK->nltype == NLTYPE_FIXED &&
            NLBLOCK->nllen == 2 &&
            c == NLBLOCK->nl[0])
          {
          could_continue = partial_newline = TRUE;
          }
        else if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
            (c < 256 &&
              (d != OP_ANY || !IS_NEWLINE(ptr)) &&
              ((ctypes[c] & toptable1[d]) ^ toptable2[d]) != 0))
          {
          if (codevalue == OP_TYPEPOSUPTO)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          if (++count >= (int)GET2(code, 1))
            { ADD_NEW(state_offset + 2 + IMM2_SIZE, 0); }
          else
            { ADD_NEW(state_offset, count); }
          }
        }
      break;

/* ========================================================================== */
      /* These are virtual opcodes that are used when something like
      OP_TYPEPLUS has OP_PROP, OP_NOTPROP, OP_ANYNL, or OP_EXTUNI as its
      argument. It keeps the code above fast for the other cases. The argument
      is in the d variable. */

#ifdef SUPPORT_UCP
      case OP_PROP_EXTRA + OP_TYPEPLUS:
      case OP_PROP_EXTRA + OP_TYPEMINPLUS:
      case OP_PROP_EXTRA + OP_TYPEPOSPLUS:
      count = current_state->count;           /* Already matched */
      if (count > 0) { ADD_ACTIVE(state_offset + 4, 0); }
      if (clen > 0)
        {
        BOOL OK;
        const pcre_uint32 *cp;
        const ucd_record * prop = GET_UCD(c);
        switch(code[2])
          {
          case PT_ANY:
          OK = TRUE;
          break;

          case PT_LAMP:
          OK = prop->chartype == ucp_Lu || prop->chartype == ucp_Ll ||
            prop->chartype == ucp_Lt;
          break;

          case PT_GC:
          OK = PRIV(ucp_gentype)[prop->chartype] == code[3];
          break;

          case PT_PC:
          OK = prop->chartype == code[3];
          break;

          case PT_SC:
          OK = prop->script == code[3];
          break;

          /* These are specials for combination cases. */

          case PT_ALNUM:
          OK = PRIV(ucp_gentype)[prop->chartype] == ucp_L ||
               PRIV(ucp_gentype)[prop->chartype] == ucp_N;
          break;

          /* Perl space used to exclude VT, but from Perl 5.18 it is included,
          which means that Perl space and POSIX space are now identical. PCRE
          was changed at release 8.34. */

          case PT_SPACE:    /* Perl space */
          case PT_PXSPACE:  /* POSIX space */
          switch(c)
            {
            HSPACE_CASES:
            VSPACE_CASES:
            OK = TRUE;
            break;

            default:
            OK = PRIV(ucp_gentype)[prop->chartype] == ucp_Z;
            break;
            }
          break;

          case PT_WORD:
          OK = PRIV(ucp_gentype)[prop->chartype] == ucp_L ||
               PRIV(ucp_gentype)[prop->chartype] == ucp_N ||
               c == CHAR_UNDERSCORE;
          break;

          case PT_CLIST:
          cp = PRIV(ucd_caseless_sets) + code[3];
          for (;;)
            {
            if (c < *cp) { OK = FALSE; break; }
            if (c == *cp++) { OK = TRUE; break; }
            }
          break;

          case PT_UCNC:
          OK = c == CHAR_DOLLAR_SIGN || c == CHAR_COMMERCIAL_AT ||
               c == CHAR_GRAVE_ACCENT || (c >= 0xa0 && c <= 0xd7ff) ||
               c >= 0xe000;
          break;

          /* Should never occur, but keep compilers from grumbling. */

          default:
          OK = codevalue != OP_PROP;
          break;
          }

        if (OK == (d == OP_PROP))
          {
          if (count > 0 && codevalue == OP_PROP_EXTRA + OP_TYPEPOSPLUS)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          count++;
          ADD_NEW(state_offset, count);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_EXTUNI_EXTRA + OP_TYPEPLUS:
      case OP_EXTUNI_EXTRA + OP_TYPEMINPLUS:
      case OP_EXTUNI_EXTRA + OP_TYPEPOSPLUS:
      count = current_state->count;  /* Already matched */
      if (count > 0) { ADD_ACTIVE(state_offset + 2, 0); }
      if (clen > 0)
        {
        int lgb, rgb;
        const pcre_uchar *nptr = ptr + clen;
        int ncount = 0;
        if (count > 0 && codevalue == OP_EXTUNI_EXTRA + OP_TYPEPOSPLUS)
          {
          active_count--;           /* Remove non-match possibility */
          next_active_state--;
          }
        lgb = UCD_GRAPHBREAK(c);
        while (nptr < end_subject)
          {
          dlen = 1;
          if (!utf) d = *nptr; else { GETCHARLEN(d, nptr, dlen); }
          rgb = UCD_GRAPHBREAK(d);
          if ((PRIV(ucp_gbtable)[lgb] & (1 << rgb)) == 0) break;
          ncount++;
          lgb = rgb;
          nptr += dlen;
          }
        count++;
        ADD_NEW_DATA(-state_offset, count, ncount);
        }
      break;
#endif

      /*-----------------------------------------------------------------*/
      case OP_ANYNL_EXTRA + OP_TYPEPLUS:
      case OP_ANYNL_EXTRA + OP_TYPEMINPLUS:
      case OP_ANYNL_EXTRA + OP_TYPEPOSPLUS:
      count = current_state->count;  /* Already matched */
      if (count > 0) { ADD_ACTIVE(state_offset + 2, 0); }
      if (clen > 0)
        {
        int ncount = 0;
        switch (c)
          {
          case CHAR_VT:
          case CHAR_FF:
          case CHAR_NEL:
#ifndef EBCDIC
          case 0x2028:
          case 0x2029:
#endif  /* Not EBCDIC */
          if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;
          goto ANYNL01;

          case CHAR_CR:
          if (ptr + 1 < end_subject && UCHAR21TEST(ptr + 1) == CHAR_LF) ncount = 1;
          /* Fall through */

          ANYNL01:
          case CHAR_LF:
          if (count > 0 && codevalue == OP_ANYNL_EXTRA + OP_TYPEPOSPLUS)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          count++;
          ADD_NEW_DATA(-state_offset, count, ncount);
          break;

          default:
          break;
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_VSPACE_EXTRA + OP_TYPEPLUS:
      case OP_VSPACE_EXTRA + OP_TYPEMINPLUS:
      case OP_VSPACE_EXTRA + OP_TYPEPOSPLUS:
      count = current_state->count;  /* Already matched */
      if (count > 0) { ADD_ACTIVE(state_offset + 2, 0); }
      if (clen > 0)
        {
        BOOL OK;
        switch (c)
          {
          VSPACE_CASES:
          OK = TRUE;
          break;

          default:
          OK = FALSE;
          break;
          }

        if (OK == (d == OP_VSPACE))
          {
          if (count > 0 && codevalue == OP_VSPACE_EXTRA + OP_TYPEPOSPLUS)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          count++;
          ADD_NEW_DATA(-state_offset, count, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_HSPACE_EXTRA + OP_TYPEPLUS:
      case OP_HSPACE_EXTRA + OP_TYPEMINPLUS:
      case OP_HSPACE_EXTRA + OP_TYPEPOSPLUS:
      count = current_state->count;  /* Already matched */
      if (count > 0) { ADD_ACTIVE(state_offset + 2, 0); }
      if (clen > 0)
        {
        BOOL OK;
        switch (c)
          {
          HSPACE_CASES:
          OK = TRUE;
          break;

          default:
          OK = FALSE;
          break;
          }

        if (OK == (d == OP_HSPACE))
          {
          if (count > 0 && codevalue == OP_HSPACE_EXTRA + OP_TYPEPOSPLUS)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          count++;
          ADD_NEW_DATA(-state_offset, count, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
#ifdef SUPPORT_UCP
      case OP_PROP_EXTRA + OP_TYPEQUERY:
      case OP_PROP_EXTRA + OP_TYPEMINQUERY:
      case OP_PROP_EXTRA + OP_TYPEPOSQUERY:
      count = 4;
      goto QS1;

      case OP_PROP_EXTRA + OP_TYPESTAR:
      case OP_PROP_EXTRA + OP_TYPEMINSTAR:
      case OP_PROP_EXTRA + OP_TYPEPOSSTAR:
      count = 0;

      QS1:

      ADD_ACTIVE(state_offset + 4, 0);
      if (clen > 0)
        {
        BOOL OK;
        const pcre_uint32 *cp;
        const ucd_record * prop = GET_UCD(c);
        switch(code[2])
          {
          case PT_ANY:
          OK = TRUE;
          break;

          case PT_LAMP:
          OK = prop->chartype == ucp_Lu || prop->chartype == ucp_Ll ||
            prop->chartype == ucp_Lt;
          break;

          case PT_GC:
          OK = PRIV(ucp_gentype)[prop->chartype] == code[3];
          break;

          case PT_PC:
          OK = prop->chartype == code[3];
          break;

          case PT_SC:
          OK = prop->script == code[3];
          break;

          /* These are specials for combination cases. */

          case PT_ALNUM:
          OK = PRIV(ucp_gentype)[prop->chartype] == ucp_L ||
               PRIV(ucp_gentype)[prop->chartype] == ucp_N;
          break;

          /* Perl space used to exclude VT, but from Perl 5.18 it is included,
          which means that Perl space and POSIX space are now identical. PCRE
          was changed at release 8.34. */

          case PT_SPACE:    /* Perl space */
          case PT_PXSPACE:  /* POSIX space */
          switch(c)
            {
            HSPACE_CASES:
            VSPACE_CASES:
            OK = TRUE;
            break;

            default:
            OK = PRIV(ucp_gentype)[prop->chartype] == ucp_Z;
            break;
            }
          break;

          case PT_WORD:
          OK = PRIV(ucp_gentype)[prop->chartype] == ucp_L ||
               PRIV(ucp_gentype)[prop->chartype] == ucp_N ||
               c == CHAR_UNDERSCORE;
          break;

          case PT_CLIST:
          cp = PRIV(ucd_caseless_sets) + code[3];
          for (;;)
            {
            if (c < *cp) { OK = FALSE; break; }
            if (c == *cp++) { OK = TRUE; break; }
            }
          break;

          case PT_UCNC:
          OK = c == CHAR_DOLLAR_SIGN || c == CHAR_COMMERCIAL_AT ||
               c == CHAR_GRAVE_ACCENT || (c >= 0xa0 && c <= 0xd7ff) ||
               c >= 0xe000;
          break;

          /* Should never occur, but keep compilers from grumbling. */

          default:
          OK = codevalue != OP_PROP;
          break;
          }

        if (OK == (d == OP_PROP))
          {
          if (codevalue == OP_PROP_EXTRA + OP_TYPEPOSSTAR ||
              codevalue == OP_PROP_EXTRA + OP_TYPEPOSQUERY)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW(state_offset + count, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_EXTUNI_EXTRA + OP_TYPEQUERY:
      case OP_EXTUNI_EXTRA + OP_TYPEMINQUERY:
      case OP_EXTUNI_EXTRA + OP_TYPEPOSQUERY:
      count = 2;
      goto QS2;

      case OP_EXTUNI_EXTRA + OP_TYPESTAR:
      case OP_EXTUNI_EXTRA + OP_TYPEMINSTAR:
      case OP_EXTUNI_EXTRA + OP_TYPEPOSSTAR:
      count = 0;

      QS2:

      ADD_ACTIVE(state_offset + 2, 0);
      if (clen > 0)
        {
        int lgb, rgb;
        const pcre_uchar *nptr = ptr + clen;
        int ncount = 0;
        if (codevalue == OP_EXTUNI_EXTRA + OP_TYPEPOSSTAR ||
            codevalue == OP_EXTUNI_EXTRA + OP_TYPEPOSQUERY)
          {
          active_count--;           /* Remove non-match possibility */
          next_active_state--;
          }
        lgb = UCD_GRAPHBREAK(c);
        while (nptr < end_subject)
          {
          dlen = 1;
          if (!utf) d = *nptr; else { GETCHARLEN(d, nptr, dlen); }
          rgb = UCD_GRAPHBREAK(d);
          if ((PRIV(ucp_gbtable)[lgb] & (1 << rgb)) == 0) break;
          ncount++;
          lgb = rgb;
          nptr += dlen;
          }
        ADD_NEW_DATA(-(state_offset + count), 0, ncount);
        }
      break;
#endif

      /*-----------------------------------------------------------------*/
      case OP_ANYNL_EXTRA + OP_TYPEQUERY:
      case OP_ANYNL_EXTRA + OP_TYPEMINQUERY:
      case OP_ANYNL_EXTRA + OP_TYPEPOSQUERY:
      count = 2;
      goto QS3;

      case OP_ANYNL_EXTRA + OP_TYPESTAR:
      case OP_ANYNL_EXTRA + OP_TYPEMINSTAR:
      case OP_ANYNL_EXTRA + OP_TYPEPOSSTAR:
      count = 0;

      QS3:
      ADD_ACTIVE(state_offset + 2, 0);
      if (clen > 0)
        {
        int ncount = 0;
        switch (c)
          {
          case CHAR_VT:
          case CHAR_FF:
          case CHAR_NEL:
#ifndef EBCDIC
          case 0x2028:
          case 0x2029:
#endif  /* Not EBCDIC */
          if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;
          goto ANYNL02;

          case CHAR_CR:
          if (ptr + 1 < end_subject && UCHAR21TEST(ptr + 1) == CHAR_LF) ncount = 1;
          /* Fall through */

          ANYNL02:
          case CHAR_LF:
          if (codevalue == OP_ANYNL_EXTRA + OP_TYPEPOSSTAR ||
              codevalue == OP_ANYNL_EXTRA + OP_TYPEPOSQUERY)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW_DATA(-(state_offset + (int)count), 0, ncount);
          break;

          default:
          break;
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_VSPACE_EXTRA + OP_TYPEQUERY:
      case OP_VSPACE_EXTRA + OP_TYPEMINQUERY:
      case OP_VSPACE_EXTRA + OP_TYPEPOSQUERY:
      count = 2;
      goto QS4;

      case OP_VSPACE_EXTRA + OP_TYPESTAR:
      case OP_VSPACE_EXTRA + OP_TYPEMINSTAR:
      case OP_VSPACE_EXTRA + OP_TYPEPOSSTAR:
      count = 0;

      QS4:
      ADD_ACTIVE(state_offset + 2, 0);
      if (clen > 0)
        {
        BOOL OK;
        switch (c)
          {
          VSPACE_CASES:
          OK = TRUE;
          break;

          default:
          OK = FALSE;
          break;
          }
        if (OK == (d == OP_VSPACE))
          {
          if (codevalue == OP_VSPACE_EXTRA + OP_TYPEPOSSTAR ||
              codevalue == OP_VSPACE_EXTRA + OP_TYPEPOSQUERY)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW_DATA(-(state_offset + (int)count), 0, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_HSPACE_EXTRA + OP_TYPEQUERY:
      case OP_HSPACE_EXTRA + OP_TYPEMINQUERY:
      case OP_HSPACE_EXTRA + OP_TYPEPOSQUERY:
      count = 2;
      goto QS5;

      case OP_HSPACE_EXTRA + OP_TYPESTAR:
      case OP_HSPACE_EXTRA + OP_TYPEMINSTAR:
      case OP_HSPACE_EXTRA + OP_TYPEPOSSTAR:
      count = 0;

      QS5:
      ADD_ACTIVE(state_offset + 2, 0);
      if (clen > 0)
        {
        BOOL OK;
        switch (c)
          {
          HSPACE_CASES:
          OK = TRUE;
          break;

          default:
          OK = FALSE;
          break;
          }

        if (OK == (d == OP_HSPACE))
          {
          if (codevalue == OP_HSPACE_EXTRA + OP_TYPEPOSSTAR ||
              codevalue == OP_HSPACE_EXTRA + OP_TYPEPOSQUERY)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW_DATA(-(state_offset + (int)count), 0, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
#ifdef SUPPORT_UCP
      case OP_PROP_EXTRA + OP_TYPEEXACT:
      case OP_PROP_EXTRA + OP_TYPEUPTO:
      case OP_PROP_EXTRA + OP_TYPEMINUPTO:
      case OP_PROP_EXTRA + OP_TYPEPOSUPTO:
      if (codevalue != OP_PROP_EXTRA + OP_TYPEEXACT)
        { ADD_ACTIVE(state_offset + 1 + IMM2_SIZE + 3, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        BOOL OK;
        const pcre_uint32 *cp;
        const ucd_record * prop = GET_UCD(c);
        switch(code[1 + IMM2_SIZE + 1])
          {
          case PT_ANY:
          OK = TRUE;
          break;

          case PT_LAMP:
          OK = prop->chartype == ucp_Lu || prop->chartype == ucp_Ll ||
            prop->chartype == ucp_Lt;
          break;

          case PT_GC:
          OK = PRIV(ucp_gentype)[prop->chartype] == code[1 + IMM2_SIZE + 2];
          break;

          case PT_PC:
          OK = prop->chartype == code[1 + IMM2_SIZE + 2];
          break;

          case PT_SC:
          OK = prop->script == code[1 + IMM2_SIZE + 2];
          break;

          /* These are specials for combination cases. */

          case PT_ALNUM:
          OK = PRIV(ucp_gentype)[prop->chartype] == ucp_L ||
               PRIV(ucp_gentype)[prop->chartype] == ucp_N;
          break;

          /* Perl space used to exclude VT, but from Perl 5.18 it is included,
          which means that Perl space and POSIX space are now identical. PCRE
          was changed at release 8.34. */

          case PT_SPACE:    /* Perl space */
          case PT_PXSPACE:  /* POSIX space */
          switch(c)
            {
            HSPACE_CASES:
            VSPACE_CASES:
            OK = TRUE;
            break;

            default:
            OK = PRIV(ucp_gentype)[prop->chartype] == ucp_Z;
            break;
            }
          break;

          case PT_WORD:
          OK = PRIV(ucp_gentype)[prop->chartype] == ucp_L ||
               PRIV(ucp_gentype)[prop->chartype] == ucp_N ||
               c == CHAR_UNDERSCORE;
          break;

          case PT_CLIST:
          cp = PRIV(ucd_caseless_sets) + code[1 + IMM2_SIZE + 2];
          for (;;)
            {
            if (c < *cp) { OK = FALSE; break; }
            if (c == *cp++) { OK = TRUE; break; }
            }
          break;

          case PT_UCNC:
          OK = c == CHAR_DOLLAR_SIGN || c == CHAR_COMMERCIAL_AT ||
               c == CHAR_GRAVE_ACCENT || (c >= 0xa0 && c <= 0xd7ff) ||
               c >= 0xe000;
          break;

          /* Should never occur, but keep compilers from grumbling. */

          default:
          OK = codevalue != OP_PROP;
          break;
          }

        if (OK == (d == OP_PROP))
          {
          if (codevalue == OP_PROP_EXTRA + OP_TYPEPOSUPTO)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          if (++count >= (int)GET2(code, 1))
            { ADD_NEW(state_offset + 1 + IMM2_SIZE + 3, 0); }
          else
            { ADD_NEW(state_offset, count); }
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_EXTUNI_EXTRA + OP_TYPEEXACT:
      case OP_EXTUNI_EXTRA + OP_TYPEUPTO:
      case OP_EXTUNI_EXTRA + OP_TYPEMINUPTO:
      case OP_EXTUNI_EXTRA + OP_TYPEPOSUPTO:
      if (codevalue != OP_EXTUNI_EXTRA + OP_TYPEEXACT)
        { ADD_ACTIVE(state_offset + 2 + IMM2_SIZE, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        int lgb, rgb;
        const pcre_uchar *nptr = ptr + clen;
        int ncount = 0;
        if (codevalue == OP_EXTUNI_EXTRA + OP_TYPEPOSUPTO)
          {
          active_count--;           /* Remove non-match possibility */
          next_active_state--;
          }
        lgb = UCD_GRAPHBREAK(c);
        while (nptr < end_subject)
          {
          dlen = 1;
          if (!utf) d = *nptr; else { GETCHARLEN(d, nptr, dlen); }
          rgb = UCD_GRAPHBREAK(d);
          if ((PRIV(ucp_gbtable)[lgb] & (1 << rgb)) == 0) break;
          ncount++;
          lgb = rgb;
          nptr += dlen;
          }
        if (nptr >= end_subject && (md->moptions & PCRE_PARTIAL_HARD) != 0)
            reset_could_continue = TRUE;
        if (++count >= (int)GET2(code, 1))
          { ADD_NEW_DATA(-(state_offset + 2 + IMM2_SIZE), 0, ncount); }
        else
          { ADD_NEW_DATA(-state_offset, count, ncount); }
        }
      break;
#endif

      /*-----------------------------------------------------------------*/
      case OP_ANYNL_EXTRA + OP_TYPEEXACT:
      case OP_ANYNL_EXTRA + OP_TYPEUPTO:
      case OP_ANYNL_EXTRA + OP_TYPEMINUPTO:
      case OP_ANYNL_EXTRA + OP_TYPEPOSUPTO:
      if (codevalue != OP_ANYNL_EXTRA + OP_TYPEEXACT)
        { ADD_ACTIVE(state_offset + 2 + IMM2_SIZE, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        int ncount = 0;
        switch (c)
          {
          case CHAR_VT:
          case CHAR_FF:
          case CHAR_NEL:
#ifndef EBCDIC
          case 0x2028:
          case 0x2029:
#endif  /* Not EBCDIC */
          if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;
          goto ANYNL03;

          case CHAR_CR:
          if (ptr + 1 < end_subject && UCHAR21TEST(ptr + 1) == CHAR_LF) ncount = 1;
          /* Fall through */

          ANYNL03:
          case CHAR_LF:
          if (codevalue == OP_ANYNL_EXTRA + OP_TYPEPOSUPTO)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          if (++count >= (int)GET2(code, 1))
            { ADD_NEW_DATA(-(state_offset + 2 + IMM2_SIZE), 0, ncount); }
          else
            { ADD_NEW_DATA(-state_offset, count, ncount); }
          break;

          default:
          break;
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_VSPACE_EXTRA + OP_TYPEEXACT:
      case OP_VSPACE_EXTRA + OP_TYPEUPTO:
      case OP_VSPACE_EXTRA + OP_TYPEMINUPTO:
      case OP_VSPACE_EXTRA + OP_TYPEPOSUPTO:
      if (codevalue != OP_VSPACE_EXTRA + OP_TYPEEXACT)
        { ADD_ACTIVE(state_offset + 2 + IMM2_SIZE, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        BOOL OK;
        switch (c)
          {
          VSPACE_CASES:
          OK = TRUE;
          break;

          default:
          OK = FALSE;
          }

        if (OK == (d == OP_VSPACE))
          {
          if (codevalue == OP_VSPACE_EXTRA + OP_TYPEPOSUPTO)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          if (++count >= (int)GET2(code, 1))
            { ADD_NEW_DATA(-(state_offset + 2 + IMM2_SIZE), 0, 0); }
          else
            { ADD_NEW_DATA(-state_offset, count, 0); }
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_HSPACE_EXTRA + OP_TYPEEXACT:
      case OP_HSPACE_EXTRA + OP_TYPEUPTO:
      case OP_HSPACE_EXTRA + OP_TYPEMINUPTO:
      case OP_HSPACE_EXTRA + OP_TYPEPOSUPTO:
      if (codevalue != OP_HSPACE_EXTRA + OP_TYPEEXACT)
        { ADD_ACTIVE(state_offset + 2 + IMM2_SIZE, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        BOOL OK;
        switch (c)
          {
          HSPACE_CASES:
          OK = TRUE;
          break;

          default:
          OK = FALSE;
          break;
          }

        if (OK == (d == OP_HSPACE))
          {
          if (codevalue == OP_HSPACE_EXTRA + OP_TYPEPOSUPTO)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          if (++count >= (int)GET2(code, 1))
            { ADD_NEW_DATA(-(state_offset + 2 + IMM2_SIZE), 0, 0); }
          else
            { ADD_NEW_DATA(-state_offset, count, 0); }
          }
        }
      break;

/* ========================================================================== */
      /* These opcodes are followed by a character that is usually compared
      to the current subject character; it is loaded into d. We still get
      here even if there is no subject character, because in some cases zero
      repetitions are permitted. */

      /*-----------------------------------------------------------------*/
      case OP_CHAR:
      if (clen > 0 && c == d) { ADD_NEW(state_offset + dlen + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_CHARI:
      if (clen == 0) break;

#ifdef SUPPORT_UTF
      if (utf)
        {
        if (c == d) { ADD_NEW(state_offset + dlen + 1, 0); } else
          {
          unsigned int othercase;
          if (c < 128)
            othercase = fcc[c];
          else
            /* If we have Unicode property support, we can use it to test the
            other case of the character. */
#ifdef SUPPORT_UCP
            othercase = UCD_OTHERCASE(c);
#else
            othercase = NOTACHAR;
#endif

          if (d == othercase) { ADD_NEW(state_offset + dlen + 1, 0); }
          }
        }
      else
#endif  /* SUPPORT_UTF */
      /* Not UTF mode */
        {
        if (TABLE_GET(c, lcc, c) == TABLE_GET(d, lcc, d))
          { ADD_NEW(state_offset + 2, 0); }
        }
      break;


#ifdef SUPPORT_UCP
      /*-----------------------------------------------------------------*/
      /* This is a tricky one because it can match more than one character.
      Find out how many characters to skip, and then set up a negative state
      to wait for them to pass before continuing. */

      case OP_EXTUNI:
      if (clen > 0)
        {
        int lgb, rgb;
        const pcre_uchar *nptr = ptr + clen;
        int ncount = 0;
        lgb = UCD_GRAPHBREAK(c);
        while (nptr < end_subject)
          {
          dlen = 1;
          if (!utf) d = *nptr; else { GETCHARLEN(d, nptr, dlen); }
          rgb = UCD_GRAPHBREAK(d);
          if ((PRIV(ucp_gbtable)[lgb] & (1 << rgb)) == 0) break;
          ncount++;
          lgb = rgb;
          nptr += dlen;
          }
        if (nptr >= end_subject && (md->moptions & PCRE_PARTIAL_HARD) != 0)
            reset_could_continue = TRUE;
        ADD_NEW_DATA(-(state_offset + 1), 0, ncount);
        }
      break;
#endif

      /*-----------------------------------------------------------------*/
      /* This is a tricky like EXTUNI because it too can match more than one
      character (when CR is followed by LF). In this case, set up a negative
      state to wait for one character to pass before continuing. */

      case OP_ANYNL:
      if (clen > 0) switch(c)
        {
        case CHAR_VT:
        case CHAR_FF:
        case CHAR_NEL:
#ifndef EBCDIC
        case 0x2028:
        case 0x2029:
#endif  /* Not EBCDIC */
        if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;

        case CHAR_LF:
        ADD_NEW(state_offset + 1, 0);
        break;

        case CHAR_CR:
        if (ptr + 1 >= end_subject)
          {
          ADD_NEW(state_offset + 1, 0);
          if ((md->moptions & PCRE_PARTIAL_HARD) != 0)
            reset_could_continue = TRUE;
          }
        else if (UCHAR21TEST(ptr + 1) == CHAR_LF)
          {
          ADD_NEW_DATA(-(state_offset + 1), 0, 1);
          }
        else
          {
          ADD_NEW(state_offset + 1, 0);
          }
        break;
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_NOT_VSPACE:
      if (clen > 0) switch(c)
        {
        VSPACE_CASES:
        break;

        default:
        ADD_NEW(state_offset + 1, 0);
        break;
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_VSPACE:
      if (clen > 0) switch(c)
        {
        VSPACE_CASES:
        ADD_NEW(state_offset + 1, 0);
        break;

        default:
        break;
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_NOT_HSPACE:
      if (clen > 0) switch(c)
        {
        HSPACE_CASES:
        break;

        default:
        ADD_NEW(state_offset + 1, 0);
        break;
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_HSPACE:
      if (clen > 0) switch(c)
        {
        HSPACE_CASES:
        ADD_NEW(state_offset + 1, 0);
        break;

        default:
        break;
        }
      break;

      /*-----------------------------------------------------------------*/
      /* Match a negated single character casefully. */

      case OP_NOT:
      if (clen > 0 && c != d) { ADD_NEW(state_offset + dlen + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      /* Match a negated single character caselessly. */

      case OP_NOTI:
      if (clen > 0)
        {
        unsigned int otherd;
#ifdef SUPPORT_UTF
        if (utf && d >= 128)
          {
#ifdef SUPPORT_UCP
          otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
          }
        else
#endif  /* SUPPORT_UTF */
        otherd = TABLE_GET(d, fcc, d);
        if (c != d && c != otherd)
          { ADD_NEW(state_offset + dlen + 1, 0); }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_PLUSI:
      case OP_MINPLUSI:
      case OP_POSPLUSI:
      case OP_NOTPLUSI:
      case OP_NOTMINPLUSI:
      case OP_NOTPOSPLUSI:
      caseless = TRUE;
      codevalue -= OP_STARI - OP_STAR;

      /* Fall through */
      case OP_PLUS:
      case OP_MINPLUS:
      case OP_POSPLUS:
      case OP_NOTPLUS:
      case OP_NOTMINPLUS:
      case OP_NOTPOSPLUS:
      count = current_state->count;  /* Already matched */
      if (count > 0) { ADD_ACTIVE(state_offset + dlen + 1, 0); }
      if (clen > 0)
        {
        pcre_uint32 otherd = NOTACHAR;
        if (caseless)
          {
#ifdef SUPPORT_UTF
          if (utf && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF */
          otherd = TABLE_GET(d, fcc, d);
          }
        if ((c == d || c == otherd) == (codevalue < OP_NOTSTAR))
          {
          if (count > 0 &&
              (codevalue == OP_POSPLUS || codevalue == OP_NOTPOSPLUS))
            {
            active_count--;             /* Remove non-match possibility */
            next_active_state--;
            }
          count++;
          ADD_NEW(state_offset, count);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_QUERYI:
      case OP_MINQUERYI:
      case OP_POSQUERYI:
      case OP_NOTQUERYI:
      case OP_NOTMINQUERYI:
      case OP_NOTPOSQUERYI:
      caseless = TRUE;
      codevalue -= OP_STARI - OP_STAR;
      /* Fall through */
      case OP_QUERY:
      case OP_MINQUERY:
      case OP_POSQUERY:
      case OP_NOTQUERY:
      case OP_NOTMINQUERY:
      case OP_NOTPOSQUERY:
      ADD_ACTIVE(state_offset + dlen + 1, 0);
      if (clen > 0)
        {
        pcre_uint32 otherd = NOTACHAR;
        if (caseless)
          {
#ifdef SUPPORT_UTF
          if (utf && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF */
          otherd = TABLE_GET(d, fcc, d);
          }
        if ((c == d || c == otherd) == (codevalue < OP_NOTSTAR))
          {
          if (codevalue == OP_POSQUERY || codevalue == OP_NOTPOSQUERY)
            {
            active_count--;            /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW(state_offset + dlen + 1, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_STARI:
      case OP_MINSTARI:
      case OP_POSSTARI:
      case OP_NOTSTARI:
      case OP_NOTMINSTARI:
      case OP_NOTPOSSTARI:
      caseless = TRUE;
      codevalue -= OP_STARI - OP_STAR;
      /* Fall through */
      case OP_STAR:
      case OP_MINSTAR:
      case OP_POSSTAR:
      case OP_NOTSTAR:
      case OP_NOTMINSTAR:
      case OP_NOTPOSSTAR:
      ADD_ACTIVE(state_offset + dlen + 1, 0);
      if (clen > 0)
        {
        pcre_uint32 otherd = NOTACHAR;
        if (caseless)
          {
#ifdef SUPPORT_UTF
          if (utf && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF */
          otherd = TABLE_GET(d, fcc, d);
          }
        if ((c == d || c == otherd) == (codevalue < OP_NOTSTAR))
          {
          if (codevalue == OP_POSSTAR || codevalue == OP_NOTPOSSTAR)
            {
            active_count--;            /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW(state_offset, 0);
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_EXACTI:
      case OP_NOTEXACTI:
      caseless = TRUE;
      codevalue -= OP_STARI - OP_STAR;
      /* Fall through */
      case OP_EXACT:
      case OP_NOTEXACT:
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        pcre_uint32 otherd = NOTACHAR;
        if (caseless)
          {
#ifdef SUPPORT_UTF
          if (utf && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF */
          otherd = TABLE_GET(d, fcc, d);
          }
        if ((c == d || c == otherd) == (codevalue < OP_NOTSTAR))
          {
          if (++count >= (int)GET2(code, 1))
            { ADD_NEW(state_offset + dlen + 1 + IMM2_SIZE, 0); }
          else
            { ADD_NEW(state_offset, count); }
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_UPTOI:
      case OP_MINUPTOI:
      case OP_POSUPTOI:
      case OP_NOTUPTOI:
      case OP_NOTMINUPTOI:
      case OP_NOTPOSUPTOI:
      caseless = TRUE;
      codevalue -= OP_STARI - OP_STAR;
      /* Fall through */
      case OP_UPTO:
      case OP_MINUPTO:
      case OP_POSUPTO:
      case OP_NOTUPTO:
      case OP_NOTMINUPTO:
      case OP_NOTPOSUPTO:
      ADD_ACTIVE(state_offset + dlen + 1 + IMM2_SIZE, 0);
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        pcre_uint32 otherd = NOTACHAR;
        if (caseless)
          {
#ifdef SUPPORT_UTF
          if (utf && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF */
          otherd = TABLE_GET(d, fcc, d);
          }
        if ((c == d || c == otherd) == (codevalue < OP_NOTSTAR))
          {
          if (codevalue == OP_POSUPTO || codevalue == OP_NOTPOSUPTO)
            {
            active_count--;             /* Remove non-match possibility */
            next_active_state--;
            }
          if (++count >= (int)GET2(code, 1))
            { ADD_NEW(state_offset + dlen + 1 + IMM2_SIZE, 0); }
          else
            { ADD_NEW(state_offset, count); }
          }
        }
      break;


/* ========================================================================== */
      /* These are the class-handling opcodes */

      case OP_CLASS:
      case OP_NCLASS:
      case OP_XCLASS:
        {
        BOOL isinclass = FALSE;
        int next_state_offset;
        const pcre_uchar *ecode;

        /* For a simple class, there is always just a 32-byte table, and we
        can set isinclass from it. */

        if (codevalue != OP_XCLASS)
          {
          ecode = code + 1 + (32 / sizeof(pcre_uchar));
          if (clen > 0)
            {
            isinclass = (c > 255)? (codevalue == OP_NCLASS) :
              ((((pcre_uint8 *)(code + 1))[c/8] & (1 << (c&7))) != 0);
            }
          }

        /* An extended class may have a table or a list of single characters,
        ranges, or both, and it may be positive or negative. There's a
        function that sorts all this out. */

        else
         {
         ecode = code + GET(code, 1);
         if (clen > 0) isinclass = PRIV(xclass)(c, code + 1 + LINK_SIZE, utf);
         }

        /* At this point, isinclass is set for all kinds of class, and ecode
        points to the byte after the end of the class. If there is a
        quantifier, this is where it will be. */

        next_state_offset = (int)(ecode - start_code);

        switch (*ecode)
          {
          case OP_CRSTAR:
          case OP_CRMINSTAR:
          case OP_CRPOSSTAR:
          ADD_ACTIVE(next_state_offset + 1, 0);
          if (isinclass)
            {
            if (*ecode == OP_CRPOSSTAR)
              {
              active_count--;           /* Remove non-match possibility */
              next_active_state--;
              }
            ADD_NEW(state_offset, 0);
            }
          break;

          case OP_CRPLUS:
          case OP_CRMINPLUS:
          case OP_CRPOSPLUS:
          count = current_state->count;  /* Already matched */
          if (count > 0) { ADD_ACTIVE(next_state_offset + 1, 0); }
          if (isinclass)
            {
            if (count > 0 && *ecode == OP_CRPOSPLUS)
              {
              active_count--;           /* Remove non-match possibility */
              next_active_state--;
              }
            count++;
            ADD_NEW(state_offset, count);
            }
          break;

          case OP_CRQUERY:
          case OP_CRMINQUERY:
          case OP_CRPOSQUERY:
          ADD_ACTIVE(next_state_offset + 1, 0);
          if (isinclass)
            {
            if (*ecode == OP_CRPOSQUERY)
              {
              active_count--;           /* Remove non-match possibility */
              next_active_state--;
              }
            ADD_NEW(next_state_offset + 1, 0);
            }
          break;

          case OP_CRRANGE:
          case OP_CRMINRANGE:
          case OP_CRPOSRANGE:
          count = current_state->count;  /* Already matched */
          if (count >= (int)GET2(ecode, 1))
            { ADD_ACTIVE(next_state_offset + 1 + 2 * IMM2_SIZE, 0); }
          if (isinclass)
            {
            int max = (int)GET2(ecode, 1 + IMM2_SIZE);
            if (*ecode == OP_CRPOSRANGE)
              {
              active_count--;           /* Remove non-match possibility */
              next_active_state--;
              }
            if (++count >= max && max != 0)   /* Max 0 => no limit */
              { ADD_NEW(next_state_offset + 1 + 2 * IMM2_SIZE, 0); }
            else
              { ADD_NEW(state_offset, count); }
            }
          break;

          default:
          if (isinclass) { ADD_NEW(next_state_offset, 0); }
          break;
          }
        }
      break;

/* ========================================================================== */
      /* These are the opcodes for fancy brackets of various kinds. We have
      to use recursion in order to handle them. The "always failing" assertion
      (?!) is optimised to OP_FAIL when compiling, so we have to support that,
      though the other "backtracking verbs" are not supported. */

      case OP_FAIL:
      forced_fail++;    /* Count FAILs for multiple states */
      break;

      case OP_ASSERT:
      case OP_ASSERT_NOT:
      case OP_ASSERTBACK:
      case OP_ASSERTBACK_NOT:
        {
        int rc;
        int local_offsets[2];
        int local_workspace[1000];
        const pcre_uchar *endasscode = code + GET(code, 1);

        while (*endasscode == OP_ALT) endasscode += GET(endasscode, 1);

        rc = internal_dfa_exec(
          md,                                   /* static match data */
          code,                                 /* this subexpression's code */
          ptr,                                  /* where we currently are */
          (int)(ptr - start_subject),           /* start offset */
          local_offsets,                        /* offset vector */
          sizeof(local_offsets)/sizeof(int),    /* size of same */
          local_workspace,                      /* workspace vector */
          sizeof(local_workspace)/sizeof(int),  /* size of same */
          rlevel);                              /* function recursion level */

        if (rc == PCRE_ERROR_DFA_UITEM) return rc;
        if ((rc >= 0) == (codevalue == OP_ASSERT || codevalue == OP_ASSERTBACK))
            { ADD_ACTIVE((int)(endasscode + LINK_SIZE + 1 - start_code), 0); }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_COND:
      case OP_SCOND:
        {
        int local_offsets[1000];
        int local_workspace[1000];
        int codelink = GET(code, 1);
        int condcode;

        /* Because of the way auto-callout works during compile, a callout item
        is inserted between OP_COND and an assertion condition. This does not
        happen for the other conditions. */

        if (code[LINK_SIZE+1] == OP_CALLOUT)
          {
          rrc = 0;
          if (PUBL(callout) != NULL)
            {
            PUBL(callout_block) cb;
            cb.version          = 1;   /* Version 1 of the callout block */
            cb.callout_number   = code[LINK_SIZE+2];
            cb.offset_vector    = offsets;
#if defined COMPILE_PCRE8
            cb.subject          = (PCRE_SPTR)start_subject;
#elif defined COMPILE_PCRE16
            cb.subject          = (PCRE_SPTR16)start_subject;
#elif defined COMPILE_PCRE32
            cb.subject          = (PCRE_SPTR32)start_subject;
#endif
            cb.subject_length   = (int)(end_subject - start_subject);
            cb.start_match      = (int)(current_subject - start_subject);
            cb.current_position = (int)(ptr - start_subject);
            cb.pattern_position = GET(code, LINK_SIZE + 3);
            cb.next_item_length = GET(code, 3 + 2*LINK_SIZE);
            cb.capture_top      = 1;
            cb.capture_last     = -1;
            cb.callout_data     = md->callout_data;
            cb.mark             = NULL;   /* No (*MARK) support */
            if ((rrc = (*PUBL(callout))(&cb)) < 0) return rrc;   /* Abandon */
            }
          if (rrc > 0) break;                      /* Fail this thread */
          code += PRIV(OP_lengths)[OP_CALLOUT];    /* Skip callout data */
          }

        condcode = code[LINK_SIZE+1];

        /* Back reference conditions and duplicate named recursion conditions
        are not supported */

        if (condcode == OP_CREF || condcode == OP_DNCREF ||
            condcode == OP_DNRREF)
          return PCRE_ERROR_DFA_UCOND;

        /* The DEFINE condition is always false */

        if (condcode == OP_DEF)
          { ADD_ACTIVE(state_offset + codelink + LINK_SIZE + 1, 0); }

        /* The only supported version of OP_RREF is for the value RREF_ANY,
        which means "test if in any recursion". We can't test for specifically
        recursed groups. */

        else if (condcode == OP_RREF)
          {
          int value = GET2(code, LINK_SIZE + 2);
          if (value != RREF_ANY) return PCRE_ERROR_DFA_UCOND;
          if (md->recursive != NULL)
            { ADD_ACTIVE(state_offset + LINK_SIZE + 2 + IMM2_SIZE, 0); }
          else { ADD_ACTIVE(state_offset + codelink + LINK_SIZE + 1, 0); }
          }

        /* Otherwise, the condition is an assertion */

        else
          {
          int rc;
          const pcre_uchar *asscode = code + LINK_SIZE + 1;
          const pcre_uchar *endasscode = asscode + GET(asscode, 1);

          while (*endasscode == OP_ALT) endasscode += GET(endasscode, 1);

          rc = internal_dfa_exec(
            md,                                   /* fixed match data */
            asscode,                              /* this subexpression's code */
            ptr,                                  /* where we currently are */
            (int)(ptr - start_subject),           /* start offset */
            local_offsets,                        /* offset vector */
            sizeof(local_offsets)/sizeof(int),    /* size of same */
            local_workspace,                      /* workspace vector */
            sizeof(local_workspace)/sizeof(int),  /* size of same */
            rlevel);                              /* function recursion level */

          if (rc == PCRE_ERROR_DFA_UITEM) return rc;
          if ((rc >= 0) ==
                (condcode == OP_ASSERT || condcode == OP_ASSERTBACK))
            { ADD_ACTIVE((int)(endasscode + LINK_SIZE + 1 - start_code), 0); }
          else
            { ADD_ACTIVE(state_offset + codelink + LINK_SIZE + 1, 0); }
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_RECURSE:
        {
        dfa_recursion_info *ri;
        int local_offsets[1000];
        int local_workspace[1000];
        const pcre_uchar *callpat = start_code + GET(code, 1);
        int recno = (callpat == md->start_code)? 0 :
          GET2(callpat, 1 + LINK_SIZE);
        int rc;

        DPRINTF(("%.*sStarting regex recursion\n", rlevel*2-2, SP));

        /* Check for repeating a recursion without advancing the subject
        pointer. This should catch convoluted mutual recursions. (Some simple
        cases are caught at compile time.) */

        for (ri = md->recursive; ri != NULL; ri = ri->prevrec)
          if (recno == ri->group_num && ptr == ri->subject_position)
            return PCRE_ERROR_RECURSELOOP;

        /* Remember this recursion and where we started it so as to
        catch infinite loops. */

        new_recursive.group_num = recno;
        new_recursive.subject_position = ptr;
        new_recursive.prevrec = md->recursive;
        md->recursive = &new_recursive;

        rc = internal_dfa_exec(
          md,                                   /* fixed match data */
          callpat,                              /* this subexpression's code */
          ptr,                                  /* where we currently are */
          (int)(ptr - start_subject),           /* start offset */
          local_offsets,                        /* offset vector */
          sizeof(local_offsets)/sizeof(int),    /* size of same */
          local_workspace,                      /* workspace vector */
          sizeof(local_workspace)/sizeof(int),  /* size of same */
          rlevel);                              /* function recursion level */

        md->recursive = new_recursive.prevrec;  /* Done this recursion */

        DPRINTF(("%.*sReturn from regex recursion: rc=%d\n", rlevel*2-2, SP,
          rc));

        /* Ran out of internal offsets */

        if (rc == 0) return PCRE_ERROR_DFA_RECURSE;

        /* For each successful matched substring, set up the next state with a
        count of characters to skip before trying it. Note that the count is in
        characters, not bytes. */

        if (rc > 0)
          {
          for (rc = rc*2 - 2; rc >= 0; rc -= 2)
            {
            int charcount = local_offsets[rc+1] - local_offsets[rc];
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
            if (utf)
              {
              const pcre_uchar *p = start_subject + local_offsets[rc];
              const pcre_uchar *pp = start_subject + local_offsets[rc+1];
              while (p < pp) if (NOT_FIRSTCHAR(*p++)) charcount--;
              }
#endif
            if (charcount > 0)
              {
              ADD_NEW_DATA(-(state_offset + LINK_SIZE + 1), 0, (charcount - 1));
              }
            else
              {
              ADD_ACTIVE(state_offset + LINK_SIZE + 1, 0);
              }
            }
          }
        else if (rc != PCRE_ERROR_NOMATCH) return rc;
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_BRAPOS:
      case OP_SBRAPOS:
      case OP_CBRAPOS:
      case OP_SCBRAPOS:
      case OP_BRAPOSZERO:
        {
        int charcount, matched_count;
        const pcre_uchar *local_ptr = ptr;
        BOOL allow_zero;

        if (codevalue == OP_BRAPOSZERO)
          {
          allow_zero = TRUE;
          codevalue = *(++code);  /* Codevalue will be one of above BRAs */
          }
        else allow_zero = FALSE;

        /* Loop to match the subpattern as many times as possible as if it were
        a complete pattern. */

        for (matched_count = 0;; matched_count++)
          {
          int local_offsets[2];
          int local_workspace[1000];

          int rc = internal_dfa_exec(
            md,                                   /* fixed match data */
            code,                                 /* this subexpression's code */
            local_ptr,                            /* where we currently are */
            (int)(ptr - start_subject),           /* start offset */
            local_offsets,                        /* offset vector */
            sizeof(local_offsets)/sizeof(int),    /* size of same */
            local_workspace,                      /* workspace vector */
            sizeof(local_workspace)/sizeof(int),  /* size of same */
            rlevel);                              /* function recursion level */

          /* Failed to match */

          if (rc < 0)
            {
            if (rc != PCRE_ERROR_NOMATCH) return rc;
            break;
            }

          /* Matched: break the loop if zero characters matched. */

          charcount = local_offsets[1] - local_offsets[0];
          if (charcount == 0) break;
          local_ptr += charcount;    /* Advance temporary position ptr */
          }

        /* At this point we have matched the subpattern matched_count
        times, and local_ptr is pointing to the character after the end of the
        last match. */

        if (matched_count > 0 || allow_zero)
          {
          const pcre_uchar *end_subpattern = code;
          int next_state_offset;

          do { end_subpattern += GET(end_subpattern, 1); }
            while (*end_subpattern == OP_ALT);
          next_state_offset =
            (int)(end_subpattern - start_code + LINK_SIZE + 1);

          /* Optimization: if there are no more active states, and there
          are no new states yet set up, then skip over the subject string
          right here, to save looping. Otherwise, set up the new state to swing
          into action when the end of the matched substring is reached. */

          if (i + 1 >= active_count && new_count == 0)
            {
            ptr = local_ptr;
            clen = 0;
            ADD_NEW(next_state_offset, 0);
            }
          else
            {
            const pcre_uchar *p = ptr;
            const pcre_uchar *pp = local_ptr;
            charcount = (int)(pp - p);
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
            if (utf) while (p < pp) if (NOT_FIRSTCHAR(*p++)) charcount--;
#endif
            ADD_NEW_DATA(-next_state_offset, 0, (charcount - 1));
            }
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_ONCE:
      case OP_ONCE_NC:
        {
        int local_offsets[2];
        int local_workspace[1000];

        int rc = internal_dfa_exec(
          md,                                   /* fixed match data */
          code,                                 /* this subexpression's code */
          ptr,                                  /* where we currently are */
          (int)(ptr - start_subject),           /* start offset */
          local_offsets,                        /* offset vector */
          sizeof(local_offsets)/sizeof(int),    /* size of same */
          local_workspace,                      /* workspace vector */
          sizeof(local_workspace)/sizeof(int),  /* size of same */
          rlevel);                              /* function recursion level */

        if (rc >= 0)
          {
          const pcre_uchar *end_subpattern = code;
          int charcount = local_offsets[1] - local_offsets[0];
          int next_state_offset, repeat_state_offset;

          do { end_subpattern += GET(end_subpattern, 1); }
            while (*end_subpattern == OP_ALT);
          next_state_offset =
            (int)(end_subpattern - start_code + LINK_SIZE + 1);

          /* If the end of this subpattern is KETRMAX or KETRMIN, we must
          arrange for the repeat state also to be added to the relevant list.
          Calculate the offset, or set -1 for no repeat. */

          repeat_state_offset = (*end_subpattern == OP_KETRMAX ||
                                 *end_subpattern == OP_KETRMIN)?
            (int)(end_subpattern - start_code - GET(end_subpattern, 1)) : -1;

          /* If we have matched an empty string, add the next state at the
          current character pointer. This is important so that the duplicate
          checking kicks in, which is what breaks infinite loops that match an
          empty string. */

          if (charcount == 0)
            {
            ADD_ACTIVE(next_state_offset, 0);
            }

          /* Optimization: if there are no more active states, and there
          are no new states yet set up, then skip over the subject string
          right here, to save looping. Otherwise, set up the new state to swing
          into action when the end of the matched substring is reached. */

          else if (i + 1 >= active_count && new_count == 0)
            {
            ptr += charcount;
            clen = 0;
            ADD_NEW(next_state_offset, 0);

            /* If we are adding a repeat state at the new character position,
            we must fudge things so that it is the only current state.
            Otherwise, it might be a duplicate of one we processed before, and
            that would cause it to be skipped. */

            if (repeat_state_offset >= 0)
              {
              next_active_state = active_states;
              active_count = 0;
              i = -1;
              ADD_ACTIVE(repeat_state_offset, 0);
              }
            }
          else
            {
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
            if (utf)
              {
              const pcre_uchar *p = start_subject + local_offsets[0];
              const pcre_uchar *pp = start_subject + local_offsets[1];
              while (p < pp) if (NOT_FIRSTCHAR(*p++)) charcount--;
              }
#endif
            ADD_NEW_DATA(-next_state_offset, 0, (charcount - 1));
            if (repeat_state_offset >= 0)
              { ADD_NEW_DATA(-repeat_state_offset, 0, (charcount - 1)); }
            }
          }
        else if (rc != PCRE_ERROR_NOMATCH) return rc;
        }
      break;


/* ========================================================================== */
      /* Handle callouts */

      case OP_CALLOUT:
      rrc = 0;
      if (PUBL(callout) != NULL)
        {
        PUBL(callout_block) cb;
        cb.version          = 1;   /* Version 1 of the callout block */
        cb.callout_number   = code[1];
        cb.offset_vector    = offsets;
#if defined COMPILE_PCRE8
        cb.subject          = (PCRE_SPTR)start_subject;
#elif defined COMPILE_PCRE16
        cb.subject          = (PCRE_SPTR16)start_subject;
#elif defined COMPILE_PCRE32
        cb.subject          = (PCRE_SPTR32)start_subject;
#endif
        cb.subject_length   = (int)(end_subject - start_subject);
        cb.start_match      = (int)(current_subject - start_subject);
        cb.current_position = (int)(ptr - start_subject);
        cb.pattern_position = GET(code, 2);
        cb.next_item_length = GET(code, 2 + LINK_SIZE);
        cb.capture_top      = 1;
        cb.capture_last     = -1;
        cb.callout_data     = md->callout_data;
        cb.mark             = NULL;   /* No (*MARK) support */
        if ((rrc = (*PUBL(callout))(&cb)) < 0) return rrc;   /* Abandon */
        }
      if (rrc == 0)
        { ADD_ACTIVE(state_offset + PRIV(OP_lengths)[OP_CALLOUT], 0); }
      break;


/* ========================================================================== */
      default:        /* Unsupported opcode */
      return PCRE_ERROR_DFA_UITEM;
      }
