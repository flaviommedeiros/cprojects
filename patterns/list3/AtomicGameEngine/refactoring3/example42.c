switch (escape)
            {
#ifdef SUPPORT_UCP
            case ESC_du:     /* These are the values given for \d etc */
            case ESC_DU:     /* when PCRE_UCP is set. We replace the */
            case ESC_wu:     /* escape sequence with an appropriate \p */
            case ESC_WU:     /* or \P to test Unicode properties instead */
            case ESC_su:     /* of the default ASCII testing. */
            case ESC_SU:
            nestptr = ptr;
            ptr = substitutes[escape - ESC_DU] - 1;  /* Just before substitute */
            class_has_8bitchar--;                /* Undo! */
            continue;
#endif
            case ESC_d:
            for (c = 0; c < 32; c++) classbits[c] |= cbits[c+cbit_digit];
            continue;

            case ESC_D:
            should_flip_negation = TRUE;
            for (c = 0; c < 32; c++) classbits[c] |= ~cbits[c+cbit_digit];
            continue;

            case ESC_w:
            for (c = 0; c < 32; c++) classbits[c] |= cbits[c+cbit_word];
            continue;

            case ESC_W:
            should_flip_negation = TRUE;
            for (c = 0; c < 32; c++) classbits[c] |= ~cbits[c+cbit_word];
            continue;

            /* Perl 5.004 onwards omitted VT from \s, but restored it at Perl
            5.18. Before PCRE 8.34, we had to preserve the VT bit if it was
            previously set by something earlier in the character class.
            Luckily, the value of CHAR_VT is 0x0b in both ASCII and EBCDIC, so
            we could just adjust the appropriate bit. From PCRE 8.34 we no
            longer treat \s and \S specially. */

            case ESC_s:
            for (c = 0; c < 32; c++) classbits[c] |= cbits[c+cbit_space];
            continue;

            case ESC_S:
            should_flip_negation = TRUE;
            for (c = 0; c < 32; c++) classbits[c] |= ~cbits[c+cbit_space];
            continue;

            /* The rest apply in both UCP and non-UCP cases. */

            case ESC_h:
            (void)add_list_to_class(classbits, &class_uchardata, options, cd,
              PRIV(hspace_list), NOTACHAR);
            continue;

            case ESC_H:
            (void)add_not_list_to_class(classbits, &class_uchardata, options,
              cd, PRIV(hspace_list));
            continue;

            case ESC_v:
            (void)add_list_to_class(classbits, &class_uchardata, options, cd,
              PRIV(vspace_list), NOTACHAR);
            continue;

            case ESC_V:
            (void)add_not_list_to_class(classbits, &class_uchardata, options,
              cd, PRIV(vspace_list));
            continue;

#ifdef SUPPORT_UCP
            case ESC_p:
            case ESC_P:
              {
              BOOL negated;
              unsigned int ptype = 0, pdata = 0;
              if (!get_ucp(&ptr, &negated, &ptype, &pdata, errorcodeptr))
                goto FAILED;
              *class_uchardata++ = ((escape == ESC_p) != negated)?
                XCL_PROP : XCL_NOTPROP;
              *class_uchardata++ = ptype;
              *class_uchardata++ = pdata;
              xclass_has_prop = TRUE;
              class_has_8bitchar--;                /* Undo! */
              continue;
              }
#endif
            /* Unrecognized escapes are faulted if PCRE is running in its
            strict mode. By default, for compatibility with Perl, they are
            treated as literals. */

            default:
            if ((options & PCRE_EXTRA) != 0)
              {
              *errorcodeptr = ERR7;
              goto FAILED;
              }
            class_has_8bitchar--;    /* Undo the speculative increase. */
            class_one_char -= 2;     /* Undo the speculative increase. */
            c = *ptr;                /* Get the final character and fall through */
            break;
            }
