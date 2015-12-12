if (base_list[0] == OP_CLASS || list[0] == OP_CLASS
#ifdef COMPILE_PCRE8
      /* In 8 bit, non-UTF mode, OP_CLASS and OP_NCLASS are the same. */
      || (!utf && (base_list[0] == OP_NCLASS || list[0] == OP_NCLASS))
#endif
      )
    {
#ifdef COMPILE_PCRE8
    if (base_list[0] == OP_CLASS || (!utf && base_list[0] == OP_NCLASS))
#else
    if (base_list[0] == OP_CLASS)
#endif
      {
      set1 = (pcre_uint8 *)(base_end - base_list[2]);
      list_ptr = list;
      }
    else
      {
      set1 = (pcre_uint8 *)(code - list[2]);
      list_ptr = base_list;
      }

    invert_bits = FALSE;
    switch(list_ptr[0])
      {
      case OP_CLASS:
      case OP_NCLASS:
      set2 = (pcre_uint8 *)
        ((list_ptr == list ? code : base_end) - list_ptr[2]);
      break;

#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
      case OP_XCLASS:
      xclass_flags = (list_ptr == list ? code : base_end) - list_ptr[2] + LINK_SIZE;
      if ((*xclass_flags & XCL_HASPROP) != 0) return FALSE;
      if ((*xclass_flags & XCL_MAP) == 0)
        {
        /* No bits are set for characters < 256. */
        if (list[1] == 0) return TRUE;
        /* Might be an empty repeat. */
        continue;
        }
      set2 = (pcre_uint8 *)(xclass_flags + 1);
      break;
#endif

      case OP_NOT_DIGIT:
      invert_bits = TRUE;
      /* Fall through */
      case OP_DIGIT:
      set2 = (pcre_uint8 *)(cd->cbits + cbit_digit);
      break;

      case OP_NOT_WHITESPACE:
      invert_bits = TRUE;
      /* Fall through */
      case OP_WHITESPACE:
      set2 = (pcre_uint8 *)(cd->cbits + cbit_space);
      break;

      case OP_NOT_WORDCHAR:
      invert_bits = TRUE;
      /* Fall through */
      case OP_WORDCHAR:
      set2 = (pcre_uint8 *)(cd->cbits + cbit_word);
      break;

      default:
      return FALSE;
      }

    /* Because the sets are unaligned, we need
    to perform byte comparison here. */
    set_end = set1 + 32;
    if (invert_bits)
      {
      do
        {
        if ((*set1++ & ~(*set2++)) != 0) return FALSE;
        }
      while (set1 < set_end);
      }
    else
      {
      do
        {
        if ((*set1++ & *set2++) != 0) return FALSE;
        }
      while (set1 < set_end);
      }

    if (list[1] == 0) return TRUE;
    /* Might be an empty repeat. */
    continue;
    }

  /* Some property combinations also acceptable. Unicode property opcodes are
  processed specially; the rest can be handled with a lookup table. */

  else
    {
    pcre_uint32 leftop, rightop;

    leftop = base_list[0];
    rightop = list[0];

#ifdef SUPPORT_UCP
    accepted = FALSE; /* Always set in non-unicode case. */
    if (leftop == OP_PROP || leftop == OP_NOTPROP)
      {
      if (rightop == OP_EOD)
        accepted = TRUE;
      else if (rightop == OP_PROP || rightop == OP_NOTPROP)
        {
        int n;
        const pcre_uint8 *p;
        BOOL same = leftop == rightop;
        BOOL lisprop = leftop == OP_PROP;
        BOOL risprop = rightop == OP_PROP;
        BOOL bothprop = lisprop && risprop;

        /* There's a table that specifies how each combination is to be
        processed:
          0   Always return FALSE (never auto-possessify)
          1   Character groups are distinct (possessify if both are OP_PROP)
          2   Check character categories in the same group (general or particular)
          3   Return TRUE if the two opcodes are not the same
          ... see comments below
        */

        n = propposstab[base_list[2]][list[2]];
        switch(n)
          {
          case 0: break;
          case 1: accepted = bothprop; break;
          case 2: accepted = (base_list[3] == list[3]) != same; break;
          case 3: accepted = !same; break;

          case 4:  /* Left general category, right particular category */
          accepted = risprop && catposstab[base_list[3]][list[3]] == same;
          break;

          case 5:  /* Right general category, left particular category */
          accepted = lisprop && catposstab[list[3]][base_list[3]] == same;
          break;

          /* This code is logically tricky. Think hard before fiddling with it.
          The posspropstab table has four entries per row. Each row relates to
          one of PCRE's special properties such as ALNUM or SPACE or WORD.
          Only WORD actually needs all four entries, but using repeats for the
          others means they can all use the same code below.

          The first two entries in each row are Unicode general categories, and
          apply always, because all the characters they include are part of the
          PCRE character set. The third and fourth entries are a general and a
          particular category, respectively, that include one or more relevant
          characters. One or the other is used, depending on whether the check
          is for a general or a particular category. However, in both cases the
          category contains more characters than the specials that are defined
          for the property being tested against. Therefore, it cannot be used
          in a NOTPROP case.

          Example: the row for WORD contains ucp_L, ucp_N, ucp_P, ucp_Po.
          Underscore is covered by ucp_P or ucp_Po. */

          case 6:  /* Left alphanum vs right general category */
          case 7:  /* Left space vs right general category */
          case 8:  /* Left word vs right general category */
          p = posspropstab[n-6];
          accepted = risprop && lisprop ==
            (list[3] != p[0] &&
             list[3] != p[1] &&
            (list[3] != p[2] || !lisprop));
          break;

          case 9:   /* Right alphanum vs left general category */
          case 10:  /* Right space vs left general category */
          case 11:  /* Right word vs left general category */
          p = posspropstab[n-9];
          accepted = lisprop && risprop ==
            (base_list[3] != p[0] &&
             base_list[3] != p[1] &&
            (base_list[3] != p[2] || !risprop));
          break;

          case 12:  /* Left alphanum vs right particular category */
          case 13:  /* Left space vs right particular category */
          case 14:  /* Left word vs right particular category */
          p = posspropstab[n-12];
          accepted = risprop && lisprop ==
            (catposstab[p[0]][list[3]] &&
             catposstab[p[1]][list[3]] &&
            (list[3] != p[3] || !lisprop));
          break;

          case 15:  /* Right alphanum vs left particular category */
          case 16:  /* Right space vs left particular category */
          case 17:  /* Right word vs left particular category */
          p = posspropstab[n-15];
          accepted = lisprop && risprop ==
            (catposstab[p[0]][base_list[3]] &&
             catposstab[p[1]][base_list[3]] &&
            (base_list[3] != p[3] || !risprop));
          break;
          }
        }
      }

    else
#endif  /* SUPPORT_UCP */

    accepted = leftop >= FIRST_AUTOTAB_OP && leftop <= LAST_AUTOTAB_LEFT_OP &&
           rightop >= FIRST_AUTOTAB_OP && rightop <= LAST_AUTOTAB_RIGHT_OP &&
           autoposstab[leftop - FIRST_AUTOTAB_OP][rightop - FIRST_AUTOTAB_OP];

    if (!accepted) return FALSE;

    if (list[1] == 0) return TRUE;
    /* Might be an empty repeat. */
    continue;
    }
