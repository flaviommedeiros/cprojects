switch (codevalue)
      {

/* ========================================================================== */
      /* Reached a closing bracket. If not at the end of the pattern, carry
      on with the next opcode. Otherwise, unless we have an empty string and
      PCRE_NOTEMPTY is set, save the match data, shifting up all previous
      matches so we always have the longest first. */

      case OP_KET:
      case OP_KETRMIN:
      case OP_KETRMAX:
      if (code != end_code)
        {
        ADD_ACTIVE(state_offset + 1 + LINK_SIZE, 0);
        if (codevalue != OP_KET)
          {
          ADD_ACTIVE(state_offset - GET(code, 1), 0);
          }
        }
      else if (ptr > current_subject || (md->moptions & PCRE_NOTEMPTY) == 0)
        {
        if (match_count < 0) match_count = (offsetcount >= 2)? 1 : 0;
          else if (match_count > 0 && ++match_count * 2 >= offsetcount)
            match_count = 0;
        count = ((match_count == 0)? offsetcount : match_count * 2) - 2;
        if (count > 0) memmove(offsets + 2, offsets, count * sizeof(int));
        if (offsetcount >= 2)
          {
          offsets[0] = current_subject - start_subject;
          offsets[1] = ptr - start_subject;
          DPRINTF(("%.*sSet matched string = \"%.*s\"\n", rlevel*2-2, SP,
            offsets[1] - offsets[0], current_subject));
          }
        if ((md->moptions & PCRE_DFA_SHORTEST) != 0)
          {
          DPRINTF(("%.*sEnd of internal_dfa_exec %d: returning %d\n"
            "%.*s---------------------\n\n", rlevel*2-2, SP, rlevel,
            match_count, rlevel*2-2, SP));
          return match_count;
          }
        }
      break;

/* ========================================================================== */
      /* These opcodes add to the current list of states without looking
      at the current character. */

      /*-----------------------------------------------------------------*/
      case OP_ALT:
      do { code += GET(code, 1); } while (*code == OP_ALT);
      ADD_ACTIVE(code - start_code, 0);
      break;

      /*-----------------------------------------------------------------*/
      case OP_BRA:
      case OP_SBRA:
      do
        {
        ADD_ACTIVE(code - start_code + 1 + LINK_SIZE, 0);
        code += GET(code, 1);
        }
      while (*code == OP_ALT);
      break;

      /*-----------------------------------------------------------------*/
      case OP_CBRA:
      case OP_SCBRA:
      ADD_ACTIVE(code - start_code + 3 + LINK_SIZE,  0);
      code += GET(code, 1);
      while (*code == OP_ALT)
        {
        ADD_ACTIVE(code - start_code + 1 + LINK_SIZE,  0);
        code += GET(code, 1);
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_BRAZERO:
      case OP_BRAMINZERO:
      ADD_ACTIVE(state_offset + 1, 0);
      code += 1 + GET(code, 2);
      while (*code == OP_ALT) code += GET(code, 1);
      ADD_ACTIVE(code - start_code + 1 + LINK_SIZE, 0);
      break;

      /*-----------------------------------------------------------------*/
      case OP_SKIPZERO:
      code += 1 + GET(code, 2);
      while (*code == OP_ALT) code += GET(code, 1);
      ADD_ACTIVE(code - start_code + 1 + LINK_SIZE, 0);
      break;

      /*-----------------------------------------------------------------*/
      case OP_CIRC:
      if ((ptr == start_subject && (md->moptions & PCRE_NOTBOL) == 0) ||
          ((ims & PCRE_MULTILINE) != 0 &&
            ptr != end_subject &&
            WAS_NEWLINE(ptr)))
        { ADD_ACTIVE(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_EOD:
      if (ptr >= end_subject) { ADD_ACTIVE(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_OPT:
      ims = code[1];
      ADD_ACTIVE(state_offset + 2, 0);
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
        { ADD_NEW(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_ALLANY:
      if (clen > 0)
        { ADD_NEW(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_EODN:
      if (clen == 0 || (IS_NEWLINE(ptr) && ptr == end_subject - md->nllen))
        { ADD_ACTIVE(state_offset + 1, 0); }
      break;

      /*-----------------------------------------------------------------*/
      case OP_DOLL:
      if ((md->moptions & PCRE_NOTEOL) == 0)
        {
        if (clen == 0 ||
            (IS_NEWLINE(ptr) &&
               ((ims & PCRE_MULTILINE) != 0 || ptr == end_subject - md->nllen)
            ))
          { ADD_ACTIVE(state_offset + 1, 0); }
        }
      else if ((ims & PCRE_MULTILINE) != 0 && IS_NEWLINE(ptr))
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
          const uschar *temp = ptr - 1;
#ifdef SUPPORT_UTF8
          if (utf8) BACKCHAR(temp);
#endif
          GETCHARTEST(d, temp);
          left_word = d < 256 && (ctypes[d] & ctype_word) != 0;
          }
        else left_word = 0;

        if (clen > 0) right_word = c < 256 && (ctypes[c] & ctype_word) != 0;
          else right_word = 0;

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
        const ucd_record * prop = GET_UCD(c);
        switch(code[1])
          {
          case PT_ANY:
          OK = TRUE;
          break;

          case PT_LAMP:
          OK = prop->chartype == ucp_Lu || prop->chartype == ucp_Ll || prop->chartype == ucp_Lt;
          break;

          case PT_GC:
          OK = _pcre_ucp_gentype[prop->chartype] == code[2];
          break;

          case PT_PC:
          OK = prop->chartype == code[2];
          break;

          case PT_SC:
          OK = prop->script == code[2];
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
        if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
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
        if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
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
        if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
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
        if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
            (c < 256 &&
              (d != OP_ANY || !IS_NEWLINE(ptr)) &&
              ((ctypes[c] & toptable1[d]) ^ toptable2[d]) != 0))
          {
          if (++count >= GET2(code, 1))
            { ADD_NEW(state_offset + 4, 0); }
          else
            { ADD_NEW(state_offset, count); }
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_TYPEUPTO:
      case OP_TYPEMINUPTO:
      case OP_TYPEPOSUPTO:
      ADD_ACTIVE(state_offset + 4, 0);
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        if ((c >= 256 && d != OP_DIGIT && d != OP_WHITESPACE && d != OP_WORDCHAR) ||
            (c < 256 &&
              (d != OP_ANY || !IS_NEWLINE(ptr)) &&
              ((ctypes[c] & toptable1[d]) ^ toptable2[d]) != 0))
          {
          if (codevalue == OP_TYPEPOSUPTO)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          if (++count >= GET2(code, 1))
            { ADD_NEW(state_offset + 4, 0); }
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
        const ucd_record * prop = GET_UCD(c);
        switch(code[2])
          {
          case PT_ANY:
          OK = TRUE;
          break;

          case PT_LAMP:
          OK = prop->chartype == ucp_Lu || prop->chartype == ucp_Ll || prop->chartype == ucp_Lt;
          break;

          case PT_GC:
          OK = _pcre_ucp_gentype[prop->chartype] == code[3];
          break;

          case PT_PC:
          OK = prop->chartype == code[3];
          break;

          case PT_SC:
          OK = prop->script == code[3];
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
      if (clen > 0 && UCD_CATEGORY(c) != ucp_M)
        {
        const uschar *nptr = ptr + clen;
        int ncount = 0;
        if (count > 0 && codevalue == OP_EXTUNI_EXTRA + OP_TYPEPOSPLUS)
          {
          active_count--;           /* Remove non-match possibility */
          next_active_state--;
          }
        while (nptr < end_subject)
          {
          int nd;
          int ndlen = 1;
          GETCHARLEN(nd, nptr, ndlen);
          if (UCD_CATEGORY(nd) != ucp_M) break;
          ncount++;
          nptr += ndlen;
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
          case 0x000b:
          case 0x000c:
          case 0x0085:
          case 0x2028:
          case 0x2029:
          if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;
          goto ANYNL01;

          case 0x000d:
          if (ptr + 1 < end_subject && ptr[1] == 0x0a) ncount = 1;
          /* Fall through */

          ANYNL01:
          case 0x000a:
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
          case 0x000a:
          case 0x000b:
          case 0x000c:
          case 0x000d:
          case 0x0085:
          case 0x2028:
          case 0x2029:
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
          case 0x09:      /* HT */
          case 0x20:      /* SPACE */
          case 0xa0:      /* NBSP */
          case 0x1680:    /* OGHAM SPACE MARK */
          case 0x180e:    /* MONGOLIAN VOWEL SEPARATOR */
          case 0x2000:    /* EN QUAD */
          case 0x2001:    /* EM QUAD */
          case 0x2002:    /* EN SPACE */
          case 0x2003:    /* EM SPACE */
          case 0x2004:    /* THREE-PER-EM SPACE */
          case 0x2005:    /* FOUR-PER-EM SPACE */
          case 0x2006:    /* SIX-PER-EM SPACE */
          case 0x2007:    /* FIGURE SPACE */
          case 0x2008:    /* PUNCTUATION SPACE */
          case 0x2009:    /* THIN SPACE */
          case 0x200A:    /* HAIR SPACE */
          case 0x202f:    /* NARROW NO-BREAK SPACE */
          case 0x205f:    /* MEDIUM MATHEMATICAL SPACE */
          case 0x3000:    /* IDEOGRAPHIC SPACE */
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
        const ucd_record * prop = GET_UCD(c);
        switch(code[2])
          {
          case PT_ANY:
          OK = TRUE;
          break;

          case PT_LAMP:
          OK = prop->chartype == ucp_Lu || prop->chartype == ucp_Ll || prop->chartype == ucp_Lt;
          break;

          case PT_GC:
          OK = _pcre_ucp_gentype[prop->chartype] == code[3];
          break;

          case PT_PC:
          OK = prop->chartype == code[3];
          break;

          case PT_SC:
          OK = prop->script == code[3];
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
      if (clen > 0 && UCD_CATEGORY(c) != ucp_M)
        {
        const uschar *nptr = ptr + clen;
        int ncount = 0;
        if (codevalue == OP_EXTUNI_EXTRA + OP_TYPEPOSSTAR ||
            codevalue == OP_EXTUNI_EXTRA + OP_TYPEPOSQUERY)
          {
          active_count--;           /* Remove non-match possibility */
          next_active_state--;
          }
        while (nptr < end_subject)
          {
          int nd;
          int ndlen = 1;
          GETCHARLEN(nd, nptr, ndlen);
          if (UCD_CATEGORY(nd) != ucp_M) break;
          ncount++;
          nptr += ndlen;
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
          case 0x000b:
          case 0x000c:
          case 0x0085:
          case 0x2028:
          case 0x2029:
          if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;
          goto ANYNL02;

          case 0x000d:
          if (ptr + 1 < end_subject && ptr[1] == 0x0a) ncount = 1;
          /* Fall through */

          ANYNL02:
          case 0x000a:
          if (codevalue == OP_ANYNL_EXTRA + OP_TYPEPOSSTAR ||
              codevalue == OP_ANYNL_EXTRA + OP_TYPEPOSQUERY)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW_DATA(-(state_offset + count), 0, ncount);
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
          case 0x000a:
          case 0x000b:
          case 0x000c:
          case 0x000d:
          case 0x0085:
          case 0x2028:
          case 0x2029:
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
          ADD_NEW_DATA(-(state_offset + count), 0, 0);
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
          case 0x09:      /* HT */
          case 0x20:      /* SPACE */
          case 0xa0:      /* NBSP */
          case 0x1680:    /* OGHAM SPACE MARK */
          case 0x180e:    /* MONGOLIAN VOWEL SEPARATOR */
          case 0x2000:    /* EN QUAD */
          case 0x2001:    /* EM QUAD */
          case 0x2002:    /* EN SPACE */
          case 0x2003:    /* EM SPACE */
          case 0x2004:    /* THREE-PER-EM SPACE */
          case 0x2005:    /* FOUR-PER-EM SPACE */
          case 0x2006:    /* SIX-PER-EM SPACE */
          case 0x2007:    /* FIGURE SPACE */
          case 0x2008:    /* PUNCTUATION SPACE */
          case 0x2009:    /* THIN SPACE */
          case 0x200A:    /* HAIR SPACE */
          case 0x202f:    /* NARROW NO-BREAK SPACE */
          case 0x205f:    /* MEDIUM MATHEMATICAL SPACE */
          case 0x3000:    /* IDEOGRAPHIC SPACE */
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
          ADD_NEW_DATA(-(state_offset + count), 0, 0);
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
        { ADD_ACTIVE(state_offset + 6, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        BOOL OK;
        const ucd_record * prop = GET_UCD(c);
        switch(code[4])
          {
          case PT_ANY:
          OK = TRUE;
          break;

          case PT_LAMP:
          OK = prop->chartype == ucp_Lu || prop->chartype == ucp_Ll || prop->chartype == ucp_Lt;
          break;

          case PT_GC:
          OK = _pcre_ucp_gentype[prop->chartype] == code[5];
          break;

          case PT_PC:
          OK = prop->chartype == code[5];
          break;

          case PT_SC:
          OK = prop->script == code[5];
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
          if (++count >= GET2(code, 1))
            { ADD_NEW(state_offset + 6, 0); }
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
        { ADD_ACTIVE(state_offset + 4, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0 && UCD_CATEGORY(c) != ucp_M)
        {
        const uschar *nptr = ptr + clen;
        int ncount = 0;
        if (codevalue == OP_EXTUNI_EXTRA + OP_TYPEPOSUPTO)
          {
          active_count--;           /* Remove non-match possibility */
          next_active_state--;
          }
        while (nptr < end_subject)
          {
          int nd;
          int ndlen = 1;
          GETCHARLEN(nd, nptr, ndlen);
          if (UCD_CATEGORY(nd) != ucp_M) break;
          ncount++;
          nptr += ndlen;
          }
        if (++count >= GET2(code, 1))
          { ADD_NEW_DATA(-(state_offset + 4), 0, ncount); }
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
        { ADD_ACTIVE(state_offset + 4, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        int ncount = 0;
        switch (c)
          {
          case 0x000b:
          case 0x000c:
          case 0x0085:
          case 0x2028:
          case 0x2029:
          if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;
          goto ANYNL03;

          case 0x000d:
          if (ptr + 1 < end_subject && ptr[1] == 0x0a) ncount = 1;
          /* Fall through */

          ANYNL03:
          case 0x000a:
          if (codevalue == OP_ANYNL_EXTRA + OP_TYPEPOSUPTO)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          if (++count >= GET2(code, 1))
            { ADD_NEW_DATA(-(state_offset + 4), 0, ncount); }
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
        { ADD_ACTIVE(state_offset + 4, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        BOOL OK;
        switch (c)
          {
          case 0x000a:
          case 0x000b:
          case 0x000c:
          case 0x000d:
          case 0x0085:
          case 0x2028:
          case 0x2029:
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
          if (++count >= GET2(code, 1))
            { ADD_NEW_DATA(-(state_offset + 4), 0, 0); }
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
        { ADD_ACTIVE(state_offset + 4, 0); }
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        BOOL OK;
        switch (c)
          {
          case 0x09:      /* HT */
          case 0x20:      /* SPACE */
          case 0xa0:      /* NBSP */
          case 0x1680:    /* OGHAM SPACE MARK */
          case 0x180e:    /* MONGOLIAN VOWEL SEPARATOR */
          case 0x2000:    /* EN QUAD */
          case 0x2001:    /* EM QUAD */
          case 0x2002:    /* EN SPACE */
          case 0x2003:    /* EM SPACE */
          case 0x2004:    /* THREE-PER-EM SPACE */
          case 0x2005:    /* FOUR-PER-EM SPACE */
          case 0x2006:    /* SIX-PER-EM SPACE */
          case 0x2007:    /* FIGURE SPACE */
          case 0x2008:    /* PUNCTUATION SPACE */
          case 0x2009:    /* THIN SPACE */
          case 0x200A:    /* HAIR SPACE */
          case 0x202f:    /* NARROW NO-BREAK SPACE */
          case 0x205f:    /* MEDIUM MATHEMATICAL SPACE */
          case 0x3000:    /* IDEOGRAPHIC SPACE */
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
          if (++count >= GET2(code, 1))
            { ADD_NEW_DATA(-(state_offset + 4), 0, 0); }
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
      case OP_CHARNC:
      if (clen == 0) break;

#ifdef SUPPORT_UTF8
      if (utf8)
        {
        if (c == d) { ADD_NEW(state_offset + dlen + 1, 0); } else
          {
          unsigned int othercase;
          if (c < 128) othercase = fcc[c]; else

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
#endif  /* SUPPORT_UTF8 */

      /* Non-UTF-8 mode */
        {
        if (lcc[c] == lcc[d]) { ADD_NEW(state_offset + 2, 0); }
        }
      break;


#ifdef SUPPORT_UCP
      /*-----------------------------------------------------------------*/
      /* This is a tricky one because it can match more than one character.
      Find out how many characters to skip, and then set up a negative state
      to wait for them to pass before continuing. */

      case OP_EXTUNI:
      if (clen > 0 && UCD_CATEGORY(c) != ucp_M)
        {
        const uschar *nptr = ptr + clen;
        int ncount = 0;
        while (nptr < end_subject)
          {
          int nclen = 1;
          GETCHARLEN(c, nptr, nclen);
          if (UCD_CATEGORY(c) != ucp_M) break;
          ncount++;
          nptr += nclen;
          }
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
        case 0x000b:
        case 0x000c:
        case 0x0085:
        case 0x2028:
        case 0x2029:
        if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;

        case 0x000a:
        ADD_NEW(state_offset + 1, 0);
        break;

        case 0x000d:
        if (ptr + 1 < end_subject && ptr[1] == 0x0a)
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
        case 0x000a:
        case 0x000b:
        case 0x000c:
        case 0x000d:
        case 0x0085:
        case 0x2028:
        case 0x2029:
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
        case 0x000a:
        case 0x000b:
        case 0x000c:
        case 0x000d:
        case 0x0085:
        case 0x2028:
        case 0x2029:
        ADD_NEW(state_offset + 1, 0);
        break;

        default: break;
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_NOT_HSPACE:
      if (clen > 0) switch(c)
        {
        case 0x09:      /* HT */
        case 0x20:      /* SPACE */
        case 0xa0:      /* NBSP */
        case 0x1680:    /* OGHAM SPACE MARK */
        case 0x180e:    /* MONGOLIAN VOWEL SEPARATOR */
        case 0x2000:    /* EN QUAD */
        case 0x2001:    /* EM QUAD */
        case 0x2002:    /* EN SPACE */
        case 0x2003:    /* EM SPACE */
        case 0x2004:    /* THREE-PER-EM SPACE */
        case 0x2005:    /* FOUR-PER-EM SPACE */
        case 0x2006:    /* SIX-PER-EM SPACE */
        case 0x2007:    /* FIGURE SPACE */
        case 0x2008:    /* PUNCTUATION SPACE */
        case 0x2009:    /* THIN SPACE */
        case 0x200A:    /* HAIR SPACE */
        case 0x202f:    /* NARROW NO-BREAK SPACE */
        case 0x205f:    /* MEDIUM MATHEMATICAL SPACE */
        case 0x3000:    /* IDEOGRAPHIC SPACE */
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
        case 0x09:      /* HT */
        case 0x20:      /* SPACE */
        case 0xa0:      /* NBSP */
        case 0x1680:    /* OGHAM SPACE MARK */
        case 0x180e:    /* MONGOLIAN VOWEL SEPARATOR */
        case 0x2000:    /* EN QUAD */
        case 0x2001:    /* EM QUAD */
        case 0x2002:    /* EN SPACE */
        case 0x2003:    /* EM SPACE */
        case 0x2004:    /* THREE-PER-EM SPACE */
        case 0x2005:    /* FOUR-PER-EM SPACE */
        case 0x2006:    /* SIX-PER-EM SPACE */
        case 0x2007:    /* FIGURE SPACE */
        case 0x2008:    /* PUNCTUATION SPACE */
        case 0x2009:    /* THIN SPACE */
        case 0x200A:    /* HAIR SPACE */
        case 0x202f:    /* NARROW NO-BREAK SPACE */
        case 0x205f:    /* MEDIUM MATHEMATICAL SPACE */
        case 0x3000:    /* IDEOGRAPHIC SPACE */
        ADD_NEW(state_offset + 1, 0);
        break;
        }
      break;

      /*-----------------------------------------------------------------*/
      /* Match a negated single character. This is only used for one-byte
      characters, that is, we know that d < 256. The character we are
      checking (c) can be multibyte. */

      case OP_NOT:
      if (clen > 0)
        {
        unsigned int otherd = ((ims & PCRE_CASELESS) != 0)? fcc[d] : d;
        if (c != d && c != otherd) { ADD_NEW(state_offset + dlen + 1, 0); }
        }
      break;

      /*-----------------------------------------------------------------*/
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
        unsigned int otherd = NOTACHAR;
        if ((ims & PCRE_CASELESS) != 0)
          {
#ifdef SUPPORT_UTF8
          if (utf8 && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF8 */
          otherd = fcc[d];
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
      case OP_QUERY:
      case OP_MINQUERY:
      case OP_POSQUERY:
      case OP_NOTQUERY:
      case OP_NOTMINQUERY:
      case OP_NOTPOSQUERY:
      ADD_ACTIVE(state_offset + dlen + 1, 0);
      if (clen > 0)
        {
        unsigned int otherd = NOTACHAR;
        if ((ims & PCRE_CASELESS) != 0)
          {
#ifdef SUPPORT_UTF8
          if (utf8 && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF8 */
          otherd = fcc[d];
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
      case OP_STAR:
      case OP_MINSTAR:
      case OP_POSSTAR:
      case OP_NOTSTAR:
      case OP_NOTMINSTAR:
      case OP_NOTPOSSTAR:
      ADD_ACTIVE(state_offset + dlen + 1, 0);
      if (clen > 0)
        {
        unsigned int otherd = NOTACHAR;
        if ((ims & PCRE_CASELESS) != 0)
          {
#ifdef SUPPORT_UTF8
          if (utf8 && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF8 */
          otherd = fcc[d];
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
      case OP_EXACT:
      case OP_NOTEXACT:
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        unsigned int otherd = NOTACHAR;
        if ((ims & PCRE_CASELESS) != 0)
          {
#ifdef SUPPORT_UTF8
          if (utf8 && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF8 */
          otherd = fcc[d];
          }
        if ((c == d || c == otherd) == (codevalue < OP_NOTSTAR))
          {
          if (++count >= GET2(code, 1))
            { ADD_NEW(state_offset + dlen + 3, 0); }
          else
            { ADD_NEW(state_offset, count); }
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_UPTO:
      case OP_MINUPTO:
      case OP_POSUPTO:
      case OP_NOTUPTO:
      case OP_NOTMINUPTO:
      case OP_NOTPOSUPTO:
      ADD_ACTIVE(state_offset + dlen + 3, 0);
      count = current_state->count;  /* Number already matched */
      if (clen > 0)
        {
        unsigned int otherd = NOTACHAR;
        if ((ims & PCRE_CASELESS) != 0)
          {
#ifdef SUPPORT_UTF8
          if (utf8 && d >= 128)
            {
#ifdef SUPPORT_UCP
            otherd = UCD_OTHERCASE(d);
#endif  /* SUPPORT_UCP */
            }
          else
#endif  /* SUPPORT_UTF8 */
          otherd = fcc[d];
          }
        if ((c == d || c == otherd) == (codevalue < OP_NOTSTAR))
          {
          if (codevalue == OP_POSUPTO || codevalue == OP_NOTPOSUPTO)
            {
            active_count--;             /* Remove non-match possibility */
            next_active_state--;
            }
          if (++count >= GET2(code, 1))
            { ADD_NEW(state_offset + dlen + 3, 0); }
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
        const uschar *ecode;

        /* For a simple class, there is always just a 32-byte table, and we
        can set isinclass from it. */

        if (codevalue != OP_XCLASS)
          {
          ecode = code + 33;
          if (clen > 0)
            {
            isinclass = (c > 255)? (codevalue == OP_NCLASS) :
              ((code[1 + c/8] & (1 << (c&7))) != 0);
            }
          }

        /* An extended class may have a table or a list of single characters,
        ranges, or both, and it may be positive or negative. There's a
        function that sorts all this out. */

        else
         {
         ecode = code + GET(code, 1);
         if (clen > 0) isinclass = _pcre_xclass(c, code + 1 + LINK_SIZE);
         }

        /* At this point, isinclass is set for all kinds of class, and ecode
        points to the byte after the end of the class. If there is a
        quantifier, this is where it will be. */

        next_state_offset = ecode - start_code;

        switch (*ecode)
          {
          case OP_CRSTAR:
          case OP_CRMINSTAR:
          ADD_ACTIVE(next_state_offset + 1, 0);
          if (isinclass) { ADD_NEW(state_offset, 0); }
          break;

          case OP_CRPLUS:
          case OP_CRMINPLUS:
          count = current_state->count;  /* Already matched */
          if (count > 0) { ADD_ACTIVE(next_state_offset + 1, 0); }
          if (isinclass) { count++; ADD_NEW(state_offset, count); }
          break;

          case OP_CRQUERY:
          case OP_CRMINQUERY:
          ADD_ACTIVE(next_state_offset + 1, 0);
          if (isinclass) { ADD_NEW(next_state_offset + 1, 0); }
          break;

          case OP_CRRANGE:
          case OP_CRMINRANGE:
          count = current_state->count;  /* Already matched */
          if (count >= GET2(ecode, 1))
            { ADD_ACTIVE(next_state_offset + 5, 0); }
          if (isinclass)
            {
            int max = GET2(ecode, 3);
            if (++count >= max && max != 0)   /* Max 0 => no limit */
              { ADD_NEW(next_state_offset + 5, 0); }
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
      to use recursion in order to handle them. The "always failing" assersion
      (?!) is optimised when compiling to OP_FAIL, so we have to support that,
      though the other "backtracking verbs" are not supported. */

      case OP_FAIL:
      break;

      case OP_ASSERT:
      case OP_ASSERT_NOT:
      case OP_ASSERTBACK:
      case OP_ASSERTBACK_NOT:
        {
        int rc;
        int local_offsets[2];
        int local_workspace[1000];
        const uschar *endasscode = code + GET(code, 1);

        while (*endasscode == OP_ALT) endasscode += GET(endasscode, 1);

        rc = internal_dfa_exec(
          md,                                   /* static match data */
          code,                                 /* this subexpression's code */
          ptr,                                  /* where we currently are */
          ptr - start_subject,                  /* start offset */
          local_offsets,                        /* offset vector */
          sizeof(local_offsets)/sizeof(int),    /* size of same */
          local_workspace,                      /* workspace vector */
          sizeof(local_workspace)/sizeof(int),  /* size of same */
          ims,                                  /* the current ims flags */
          rlevel,                               /* function recursion level */
          recursing);                           /* pass on regex recursion */

        if ((rc >= 0) == (codevalue == OP_ASSERT || codevalue == OP_ASSERTBACK))
            { ADD_ACTIVE(endasscode + LINK_SIZE + 1 - start_code, 0); }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_COND:
      case OP_SCOND:
        {
        int local_offsets[1000];
        int local_workspace[1000];
        int condcode = code[LINK_SIZE+1];

        /* Back reference conditions are not supported */

        if (condcode == OP_CREF) return PCRE_ERROR_DFA_UCOND;

        /* The DEFINE condition is always false */

        if (condcode == OP_DEF)
          {
          ADD_ACTIVE(state_offset + GET(code, 1) + LINK_SIZE + 1, 0);
          }

        /* The only supported version of OP_RREF is for the value RREF_ANY,
        which means "test if in any recursion". We can't test for specifically
        recursed groups. */

        else if (condcode == OP_RREF)
          {
          int value = GET2(code, LINK_SIZE+2);
          if (value != RREF_ANY) return PCRE_ERROR_DFA_UCOND;
          if (recursing > 0) { ADD_ACTIVE(state_offset + LINK_SIZE + 4, 0); }
            else { ADD_ACTIVE(state_offset + GET(code, 1) + LINK_SIZE + 1, 0); }
          }

        /* Otherwise, the condition is an assertion */

        else
          {
          int rc;
          const uschar *asscode = code + LINK_SIZE + 1;
          const uschar *endasscode = asscode + GET(asscode, 1);

          while (*endasscode == OP_ALT) endasscode += GET(endasscode, 1);

          rc = internal_dfa_exec(
            md,                                   /* fixed match data */
            asscode,                              /* this subexpression's code */
            ptr,                                  /* where we currently are */
            ptr - start_subject,                  /* start offset */
            local_offsets,                        /* offset vector */
            sizeof(local_offsets)/sizeof(int),    /* size of same */
            local_workspace,                      /* workspace vector */
            sizeof(local_workspace)/sizeof(int),  /* size of same */
            ims,                                  /* the current ims flags */
            rlevel,                               /* function recursion level */
            recursing);                           /* pass on regex recursion */

          if ((rc >= 0) ==
                (condcode == OP_ASSERT || condcode == OP_ASSERTBACK))
            { ADD_ACTIVE(endasscode + LINK_SIZE + 1 - start_code, 0); }
          else
            { ADD_ACTIVE(state_offset + GET(code, 1) + LINK_SIZE + 1, 0); }
          }
        }
      break;

      /*-----------------------------------------------------------------*/
      case OP_RECURSE:
        {
        int local_offsets[1000];
        int local_workspace[1000];
        int rc;

        DPRINTF(("%.*sStarting regex recursion %d\n", rlevel*2-2, SP,
          recursing + 1));

        rc = internal_dfa_exec(
          md,                                   /* fixed match data */
          start_code + GET(code, 1),            /* this subexpression's code */
          ptr,                                  /* where we currently are */
          ptr - start_subject,                  /* start offset */
          local_offsets,                        /* offset vector */
          sizeof(local_offsets)/sizeof(int),    /* size of same */
          local_workspace,                      /* workspace vector */
          sizeof(local_workspace)/sizeof(int),  /* size of same */
          ims,                                  /* the current ims flags */
          rlevel,                               /* function recursion level */
          recursing + 1);                       /* regex recurse level */

        DPRINTF(("%.*sReturn from regex recursion %d: rc=%d\n", rlevel*2-2, SP,
          recursing + 1, rc));

        /* Ran out of internal offsets */

        if (rc == 0) return PCRE_ERROR_DFA_RECURSE;

        /* For each successful matched substring, set up the next state with a
        count of characters to skip before trying it. Note that the count is in
        characters, not bytes. */

        if (rc > 0)
          {
          for (rc = rc*2 - 2; rc >= 0; rc -= 2)
            {
            const uschar *p = start_subject + local_offsets[rc];
            const uschar *pp = start_subject + local_offsets[rc+1];
            int charcount = local_offsets[rc+1] - local_offsets[rc];
            while (p < pp) if ((*p++ & 0xc0) == 0x80) charcount--;
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
      case OP_ONCE:
        {
        int local_offsets[2];
        int local_workspace[1000];

        int rc = internal_dfa_exec(
          md,                                   /* fixed match data */
          code,                                 /* this subexpression's code */
          ptr,                                  /* where we currently are */
          ptr - start_subject,                  /* start offset */
          local_offsets,                        /* offset vector */
          sizeof(local_offsets)/sizeof(int),    /* size of same */
          local_workspace,                      /* workspace vector */
          sizeof(local_workspace)/sizeof(int),  /* size of same */
          ims,                                  /* the current ims flags */
          rlevel,                               /* function recursion level */
          recursing);                           /* pass on regex recursion */

        if (rc >= 0)
          {
          const uschar *end_subpattern = code;
          int charcount = local_offsets[1] - local_offsets[0];
          int next_state_offset, repeat_state_offset;

          do { end_subpattern += GET(end_subpattern, 1); }
            while (*end_subpattern == OP_ALT);
          next_state_offset = end_subpattern - start_code + LINK_SIZE + 1;

          /* If the end of this subpattern is KETRMAX or KETRMIN, we must
          arrange for the repeat state also to be added to the relevant list.
          Calculate the offset, or set -1 for no repeat. */

          repeat_state_offset = (*end_subpattern == OP_KETRMAX ||
                                 *end_subpattern == OP_KETRMIN)?
            end_subpattern - start_code - GET(end_subpattern, 1) : -1;

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
          into action when the end of the substring is reached. */

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
            const uschar *p = start_subject + local_offsets[0];
            const uschar *pp = start_subject + local_offsets[1];
            while (p < pp) if ((*p++ & 0xc0) == 0x80) charcount--;
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
      if (pcre_callout != NULL)
        {
        int rrc;
        pcre_callout_block cb;
        cb.version          = 1;   /* Version 1 of the callout block */
        cb.callout_number   = code[1];
        cb.offset_vector    = offsets;
        cb.subject          = (PCRE_SPTR)start_subject;
        cb.subject_length   = end_subject - start_subject;
        cb.start_match      = current_subject - start_subject;
        cb.current_position = ptr - start_subject;
        cb.pattern_position = GET(code, 2);
        cb.next_item_length = GET(code, 2 + LINK_SIZE);
        cb.capture_top      = 1;
        cb.capture_last     = -1;
        cb.callout_data     = md->callout_data;
        if ((rrc = (*pcre_callout)(&cb)) < 0) return rrc;   /* Abandon */
        if (rrc == 0) { ADD_ACTIVE(state_offset + 2 + 2*LINK_SIZE, 0); }
        }
      break;


/* ========================================================================== */
      default:        /* Unsupported opcode */
      return PCRE_ERROR_DFA_UITEM;
      }
