#ifdef SUPPORT_UTF
if (utf && NOT_FIRSTCHAR(code[-1]))
        {
        pcre_uchar *lastchar = code - 1;
        BACKCHAR(lastchar);
        c = (int)(code - lastchar);     /* Length of UTF-8 character */
        memcpy(utf_chars, lastchar, IN_UCHARS(c)); /* Save the char */
        c |= UTF_LENGTH;                /* Flag c as a length */
        }
      else
#endif /* SUPPORT_UTF */

      /* Handle the case of a single charater - either with no UTF support, or
      with UTF disabled, or for a single character UTF character. */
        {
        c = code[-1];
        if (*previous <= OP_CHARI && repeat_min > 1)
          reqchar = c | req_caseopt | cd->req_varyopt;
        }
