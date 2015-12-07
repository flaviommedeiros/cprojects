#ifdef SUPPORT_UCP
if (utf && (options & PCRE_CASELESS) != 0)
#else
          if ((options & PCRE_CASELESS) != 0)
#endif
            {
            unsigned int occ, ocd;
            unsigned int cc = c;
            unsigned int origd = d;
            while (get_othercase_range(&cc, origd, &occ, &ocd))
              {
              if (occ >= (unsigned int)c &&
                  ocd <= (unsigned int)d)
                continue;                          /* Skip embedded ranges */

              if (occ < (unsigned int)c  &&
                  ocd >= (unsigned int)c - 1)      /* Extend the basic range */
                {                                  /* if there is overlap,   */
                c = occ;                           /* noting that if occ < c */
                continue;                          /* we can't have ocd > d  */
                }                                  /* because a subrange is  */
              if (ocd > (unsigned int)d &&
                  occ <= (unsigned int)d + 1)      /* always shorter than    */
                {                                  /* the basic range.       */
                d = ocd;
                continue;
                }

              if (occ == ocd)
                {
                *class_uchardata++ = XCL_SINGLE;
                }
              else
                {
                *class_uchardata++ = XCL_RANGE;
                class_uchardata += PRIV(ord2utf)(occ, class_uchardata);
                }
              class_uchardata += PRIV(ord2utf)(ocd, class_uchardata);
              }
            }
