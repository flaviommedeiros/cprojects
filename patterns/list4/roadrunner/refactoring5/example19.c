#ifdef SUPPORT_UTF8
if (utf8 && (code[-1] & 0x80) != 0)
        {
        uschar *lastchar = code - 1;
        while((*lastchar & 0xc0) == 0x80) lastchar--;
        c = code - lastchar;            /* Length of UTF-8 character */
        memcpy(utf8_char, lastchar, c); /* Save the char */
        c |= 0x80;                      /* Flag c as a length */
        }
      else
#endif

      /* Handle the case of a single byte - either with no UTF8 support, or
      with UTF-8 disabled, or for a UTF-8 character < 128. */

        {
        c = code[-1];
        if (repeat_min > 1) reqbyte = c | req_caseopt | cd->req_varyopt;
        }
