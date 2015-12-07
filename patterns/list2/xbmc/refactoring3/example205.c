switch (op)
    {
    case OP_CBRA:
    case OP_SCBRA:
    case OP_BRA:
    case OP_SBRA:
    case OP_ONCE:
    case OP_COND:
    case OP_SCOND:
    d = find_minlength(cc, startcode, options);
    if (d < 0) return d;
    branchlength += d;
    do cc += GET(cc, 1); while (*cc == OP_ALT);
    cc += 1 + LINK_SIZE;
    break;

    /* Reached end of a branch; if it's a ket it is the end of a nested
    call. If it's ALT it is an alternation in a nested call. If it is
    END it's the end of the outer call. All can be handled by the same code. */

    case OP_ALT:
    case OP_KET:
    case OP_KETRMAX:
    case OP_KETRMIN:
    case OP_END:
    if (length < 0 || (!had_recurse && branchlength < length))
      length = branchlength;
    if (*cc != OP_ALT) return length;
    cc += 1 + LINK_SIZE;
    branchlength = 0;
    had_recurse = FALSE;
    break;

    /* Skip over assertive subpatterns */

    case OP_ASSERT:
    case OP_ASSERT_NOT:
    case OP_ASSERTBACK:
    case OP_ASSERTBACK_NOT:
    do cc += GET(cc, 1); while (*cc == OP_ALT);
    /* Fall through */

    /* Skip over things that don't match chars */

    case OP_REVERSE:
    case OP_CREF:
    case OP_NCREF:
    case OP_RREF:
    case OP_NRREF:
    case OP_DEF:
    case OP_OPT:
    case OP_CALLOUT:
    case OP_SOD:
    case OP_SOM:
    case OP_EOD:
    case OP_EODN:
    case OP_CIRC:
    case OP_DOLL:
    case OP_NOT_WORD_BOUNDARY:
    case OP_WORD_BOUNDARY:
    cc += _pcre_OP_lengths[*cc];
    break;

    /* Skip over a subpattern that has a {0} or {0,x} quantifier */

    case OP_BRAZERO:
    case OP_BRAMINZERO:
    case OP_SKIPZERO:
    cc += _pcre_OP_lengths[*cc];
    do cc += GET(cc, 1); while (*cc == OP_ALT);
    cc += 1 + LINK_SIZE;
    break;

    /* Handle literal characters and + repetitions */

    case OP_CHAR:
    case OP_CHARNC:
    case OP_NOT:
    case OP_PLUS:
    case OP_MINPLUS:
    case OP_POSPLUS:
    case OP_NOTPLUS:
    case OP_NOTMINPLUS:
    case OP_NOTPOSPLUS:
    branchlength++;
    cc += 2;
#ifdef SUPPORT_UTF8
    if (utf8 && cc[-1] >= 0xc0) cc += _pcre_utf8_table4[cc[-1] & 0x3f];
#endif
    break;

    case OP_TYPEPLUS:
    case OP_TYPEMINPLUS:
    case OP_TYPEPOSPLUS:
    branchlength++;
    cc += (cc[1] == OP_PROP || cc[1] == OP_NOTPROP)? 4 : 2;
    break;

    /* Handle exact repetitions. The count is already in characters, but we
    need to skip over a multibyte character in UTF8 mode.  */

    case OP_EXACT:
    case OP_NOTEXACT:
    branchlength += GET2(cc,1);
    cc += 4;
#ifdef SUPPORT_UTF8
    if (utf8 && cc[-1] >= 0xc0) cc += _pcre_utf8_table4[cc[-1] & 0x3f];
#endif
    break;

    case OP_TYPEEXACT:
    branchlength += GET2(cc,1);
    cc += (cc[3] == OP_PROP || cc[3] == OP_NOTPROP)? 6 : 4;
    break;

    /* Handle single-char non-literal matchers */

    case OP_PROP:
    case OP_NOTPROP:
    cc += 2;
    /* Fall through */

    case OP_NOT_DIGIT:
    case OP_DIGIT:
    case OP_NOT_WHITESPACE:
    case OP_WHITESPACE:
    case OP_NOT_WORDCHAR:
    case OP_WORDCHAR:
    case OP_ANY:
    case OP_ALLANY:
    case OP_EXTUNI:
    case OP_HSPACE:
    case OP_NOT_HSPACE:
    case OP_VSPACE:
    case OP_NOT_VSPACE:
    branchlength++;
    cc++;
    break;

    /* "Any newline" might match two characters */

    case OP_ANYNL:
    branchlength += 2;
    cc++;
    break;

    /* The single-byte matcher means we can't proceed in UTF-8 mode */

    case OP_ANYBYTE:
#ifdef SUPPORT_UTF8
    if (utf8) return -1;
#endif
    branchlength++;
    cc++;
    break;

    /* For repeated character types, we have to test for \p and \P, which have
    an extra two bytes of parameters. */

    case OP_TYPESTAR:
    case OP_TYPEMINSTAR:
    case OP_TYPEQUERY:
    case OP_TYPEMINQUERY:
    case OP_TYPEPOSSTAR:
    case OP_TYPEPOSQUERY:
    if (cc[1] == OP_PROP || cc[1] == OP_NOTPROP) cc += 2;
    cc += _pcre_OP_lengths[op];
    break;

    case OP_TYPEUPTO:
    case OP_TYPEMINUPTO:
    case OP_TYPEPOSUPTO:
    if (cc[3] == OP_PROP || cc[3] == OP_NOTPROP) cc += 2;
    cc += _pcre_OP_lengths[op];
    break;

    /* Check a class for variable quantification */

#ifdef SUPPORT_UTF8
    case OP_XCLASS:
    cc += GET(cc, 1) - 33;
    /* Fall through */
#endif

    case OP_CLASS:
    case OP_NCLASS:
    cc += 33;

    switch (*cc)
      {
      case OP_CRPLUS:
      case OP_CRMINPLUS:
      branchlength++;
      /* Fall through */

      case OP_CRSTAR:
      case OP_CRMINSTAR:
      case OP_CRQUERY:
      case OP_CRMINQUERY:
      cc++;
      break;

      case OP_CRRANGE:
      case OP_CRMINRANGE:
      branchlength += GET2(cc,1);
      cc += 5;
      break;

      default:
      branchlength++;
      break;
      }
    break;

    /* Backreferences and subroutine calls are treated in the same way: we find
    the minimum length for the subpattern. A recursion, however, causes an
    a flag to be set that causes the length of this branch to be ignored. The
    logic is that a recursion can only make sense if there is another
    alternation that stops the recursing. That will provide the minimum length
    (when no recursion happens). A backreference within the group that it is
    referencing behaves in the same way.

    If PCRE_JAVASCRIPT_COMPAT is set, a backreference to an unset bracket
    matches an empty string (by default it causes a matching failure), so in
    that case we must set the minimum length to zero. */

    case OP_REF:
    if ((options & PCRE_JAVASCRIPT_COMPAT) == 0)
      {
      ce = cs = (uschar *)_pcre_find_bracket(startcode, utf8, GET2(cc, 1));
      if (cs == NULL) return -2;
      do ce += GET(ce, 1); while (*ce == OP_ALT);
      if (cc > cs && cc < ce)
        {
        d = 0;
        had_recurse = TRUE;
        }
      else d = find_minlength(cs, startcode, options);
      }
    else d = 0;
    cc += 3;

    /* Handle repeated back references */

    switch (*cc)
      {
      case OP_CRSTAR:
      case OP_CRMINSTAR:
      case OP_CRQUERY:
      case OP_CRMINQUERY:
      min = 0;
      cc++;
      break;

      case OP_CRRANGE:
      case OP_CRMINRANGE:
      min = GET2(cc, 1);
      cc += 5;
      break;

      default:
      min = 1;
      break;
      }

    branchlength += min * d;
    break;

    case OP_RECURSE:
    cs = ce = (uschar *)startcode + GET(cc, 1);
    if (cs == NULL) return -2;
    do ce += GET(ce, 1); while (*ce == OP_ALT);
    if (cc > cs && cc < ce)
      had_recurse = TRUE;
    else
      branchlength += find_minlength(cs, startcode, options);
    cc += 1 + LINK_SIZE;
    break;

    /* Anything else does not or need not match a character. We can get the
    item's length from the table, but for those that can match zero occurrences
    of a character, we must take special action for UTF-8 characters. */

    case OP_UPTO:
    case OP_NOTUPTO:
    case OP_MINUPTO:
    case OP_NOTMINUPTO:
    case OP_POSUPTO:
    case OP_STAR:
    case OP_MINSTAR:
    case OP_NOTMINSTAR:
    case OP_POSSTAR:
    case OP_NOTPOSSTAR:
    case OP_QUERY:
    case OP_MINQUERY:
    case OP_NOTMINQUERY:
    case OP_POSQUERY:
    case OP_NOTPOSQUERY:
    cc += _pcre_OP_lengths[op];
#ifdef SUPPORT_UTF8
    if (utf8 && cc[-1] >= 0xc0) cc += _pcre_utf8_table4[cc[-1] & 0x3f];
#endif
    break;

    /* For the record, these are the opcodes that are matched by "default":
    OP_ACCEPT, OP_CLOSE, OP_COMMIT, OP_FAIL, OP_PRUNE, OP_SET_SOM, OP_SKIP,
    OP_THEN. */

    default:
    cc += _pcre_OP_lengths[op];
    break;
    }
