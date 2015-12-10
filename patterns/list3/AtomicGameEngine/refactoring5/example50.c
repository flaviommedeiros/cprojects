#ifdef SUPPORT_UCP
if ((options & PCRE_UTF8) != 0)
    {
    int rc;
    pcre_uint32 oc, od;

    options &= ~PCRE_CASELESS;   /* Remove for recursive calls */
    c = start;

    while ((rc = get_othercase_range(&c, end, &oc, &od)) >= 0)
      {
      /* Handle a single character that has more than one other case. */

      if (rc > 0) n8 += add_list_to_class(classbits, uchardptr, options, cd,
        PRIV(ucd_caseless_sets) + rc, oc);

      /* Do nothing if the other case range is within the original range. */

      else if (oc >= start && od <= end) continue;

      /* Extend the original range if there is overlap, noting that if oc < c, we
      can't have od > end because a subrange is always shorter than the basic
      range. Otherwise, use a recursive call to add the additional range. */

      else if (oc < start && od >= start - 1) start = oc; /* Extend downwards */
      else if (od > end && oc <= end + 1) end = od;       /* Extend upwards */
      else n8 += add_to_class(classbits, uchardptr, options, cd, oc, od);
      }
    }
  else
#endif  /* SUPPORT_UCP */

  /* Not UTF-mode, or no UCP */

  for (c = start; c <= classbits_end; c++)
    {
    SETBIT(classbits, cd->fcc[c]);
    n8++;
    }
