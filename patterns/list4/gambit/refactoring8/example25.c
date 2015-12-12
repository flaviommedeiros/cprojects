___HIDDEN ___SCMOBJ lineeditor_output_terminal_emulate
   ___P((___device_tty *self,
         ___C *buf,
         int len),
        (self,
         buf,
         len)
___device_tty *self;
___C *buf;
int len;)
{
  /*
   * This routine processes a string of characters (possibly
   * containing control characters and escape sequences) that the
   * emulated terminal received.  It also tracks the movement of the
   * emulated terminal's cursor.
   */

  ___device_tty *d = self;
  ___SCMOBJ e;
  int pn;
  ___C c;

#ifdef ___DEBUG_TTY

  {
    int i;

    ___printf ("lineeditor_output_terminal_emulate len: %d  ", len);

    ___printf ("\"");

    for (i=0; i<len; i++)
      if (buf[i] < 32 || buf[i] >= 127)
        ___printf ("\\x%02x", buf[i]);
      else
        ___printf ("%c", buf[i]);

    ___printf ("\"\n");
  }

#endif

  pn = d->terminal_param_num;

  while (len > 0)
    {
      ___C c = *buf++;

      len--;

      if (!d->editing_line)
        {
          /* accumulate prompt */

          int i = d->prompt_length;
          if (i < ___CAST(int,___NBELEMS(d->prompt)))
            {
              d->prompt[i] = c;
              d->prompt_length = i+1;
            }
        }

      switch (pn)
        {
        case -2:
          {
            /* outside of an escape sequence */

            if (c >= ___UNICODE_SPACE)
              {
                int n = 0;

                while (n < len && *buf >= ___UNICODE_SPACE)
                  {
                    n++;
                    buf++;
                  }

                if (!d->editing_line)
                  {
                    /* accumulate prompt */

                    ___C *p = buf - n;
                    int i = d->prompt_length;
                    while (i < ___CAST(int,___NBELEMS(d->prompt)) && p < buf)
                      d->prompt[i++] = *p++;
                    d->prompt_length = i;
                  }

                len -= n;
                n++;

                if ((e = lineeditor_output_terminal_plain_chars (d, buf-n, n))
                    != ___FIX(___NO_ERR))
                  {
                    d->terminal_param_num = pn;
                    return e;
                  }
              }
            else if (c != ___UNICODE_ESCAPE) /* non ESC control character? */
              {
                if (c == ___UNICODE_LINEFEED)
                  {
                    if (!d->editing_line)
                      d->prompt_length = 0; /* reset prompt */

                    /******** TODO: should check if cr-lf, etc is needed */

                    if ((e = lineeditor_output_terminal_op
                               (d,
                                TERMINAL_CTRL - c,
                                0,
                                NULL))
                        != ___FIX(___NO_ERR))
                      {
                        d->terminal_param_num = pn;
                        return e;
                      }
                  }
                else
                  {
                    if ((e = lineeditor_output_terminal_op
                               (d,
                                TERMINAL_CTRL - c,
                                0,
                                NULL))
                        != ___FIX(___NO_ERR))
                      {
                        d->terminal_param_num = pn;
                        return e;
                      }
                  }
              }
            else
              pn = -1; /* start of an escape sequence */

            break;
          }

        case -1:
          {
            /* after an ESC */

            if (c == '[')
              {
                d->terminal_op_type = 0;
                pn = 0;
                d->terminal_param[0] = 0;
              }
            else if (c == ']')
              {
                d->terminal_op_type = 1;
                pn = 0;
                d->terminal_param[0] = 0;
              }
            else
              pn = -2;

            break;
          }

        default:
          {
            /* accumulating parameters after an ESC '[' */

            if (d->terminal_op_type == 1 && pn == 1)
              {
                if (c == ___UNICODE_BELL)
                  {
                    pn = -2;

                    if ((e = lineeditor_output_terminal_op
                               (d,
                                TERMINAL_WINDOW_OP,
                                d->terminal_param[0],
                                d->terminal_param_text))
                        != ___FIX(___NO_ERR))
                      {
                        d->terminal_param_num = pn;
                        return e;
                      }
                  }
                else
                  {
                    if (d->terminal_param[1] <
                        ___CAST(int,___NBELEMS(d->terminal_param_text))-1)
                      d->terminal_param_text[d->terminal_param[1]++] = c;
                  }
              }
            else if (c >= '0' && c <= '9')
              {
                int x = c - '0';
                int p = d->terminal_param[pn];
                if (p < 1000)
                  d->terminal_param[pn] = p*10 + x;
              }
            else if (c == ';')
              {
                if (pn < ___CAST(int,___NBELEMS(d->terminal_param))-1)
                  pn++;
                d->terminal_param[pn] = 0;
              }
            else
              {
                int op = TERMINAL_NOOP;
                int arg = 0;

                if (c == 'A')
                  {
                    op = TERMINAL_MOVE_ROW;
                    arg = -d->terminal_param[0];
                    if (arg >= 0) arg = -1;
                  }
                else if (c == 'B')
                  {
                    op = TERMINAL_MOVE_ROW;
                    arg = d->terminal_param[0];
                    if (arg <= 0) arg = 1;
                  }
                else if (c == 'C')
                  {
                    op = TERMINAL_MOVE_COL;
                    arg = d->terminal_param[0];
                    if (arg <= 0) arg = 1;
                  }
                else if (c == 'D')
                  {
                    op = TERMINAL_MOVE_COL;
                    arg = -d->terminal_param[0];
                    if (arg >= 0) arg = -1;
                  }
                else if (c == 'H' || c == 'f')
                  {
                    op = d->terminal_param[0];
                    if (op <= 0) op = 1;
                    op += TERMINAL_MOVE_ABS - 1;
                    arg = d->terminal_param[1];
                    if (pn < 1 || arg <= 0) arg = 1;
                    arg--;
                  }
                else if (c == 'J')
                  {
                    op = TERMINAL_ERASE_DISP;
                    arg = d->terminal_param[0];
                    if (arg <= 0) arg = 0;
                  }
                else if (c == 'K')
                  {
                    op = TERMINAL_ERASE_LINE;
                    arg = d->terminal_param[0];
                    if (arg <= 0) arg = 0;
                  }
                else if (c == 'm')
                  {
                    int j;
                    int style;
                    int fg;
                    int bg;

                    op = TERMINAL_SET_ATTRS;
                    arg = d->current.attrs;
                    style = GET_STYLE(arg);
                    fg = GET_FOREGROUND_COLOR(arg);
                    bg = GET_BACKGROUND_COLOR(arg);

                    for (j=0; j<=pn; j++)
                      {
                        int x = d->terminal_param[j];
                        if (x <= 0)
                          {
                            style = TEXT_STYLE_NORMAL;
                            fg = DEFAULT_TEXT_COLOR;
                            bg = DEFAULT_TEXT_COLOR;
                          }
                        else if (x == 1)
                          style |= TEXT_STYLE_BOLD;
                        else if (x == 4)
                          style |= TEXT_STYLE_UNDERLINE;
                        else if (x == 7)
                          style |= TEXT_STYLE_REVERSE;
                        else if (x >= 30 && x <= 37)
                          fg = x-30;
                        else if (x >= 40 && x <= 47)
                          bg = x-40;
                      }
                    arg = MAKE_TEXT_ATTRS(style,fg,bg);
                  }
                else if (c == 't')
                  {
                    switch (d->terminal_param[0])
                      {
                      case 3:
                      case 4:
                      case 8:
                        if (pn == 2 &&
                            d->terminal_param[1] <= 4095 &&
                            d->terminal_param[2] <= 4095)
                          {
                            arg = (d->terminal_param[2] << 20) +
                                  (d->terminal_param[1] << 8) +
                                  d->terminal_param[0];
                            op = TERMINAL_WINDOW_OP;
                          }
                        break;

                      case 9:
                        if (pn == 1 &&
                            d->terminal_param[1] <= 4095)
                          {
                            arg = (d->terminal_param[1] << 8) +
                                  d->terminal_param[0];
                            op = TERMINAL_WINDOW_OP;
                          }
                        break;

                      default:
                        if (pn == 0 &&
                            d->terminal_param[0] >= 1 &&
                            d->terminal_param[0] <= 9)
                          {
                            arg = d->terminal_param[0];
                            op = TERMINAL_WINDOW_OP;
                          }
                        break;
                      }
                  }

                pn = -2;

                if ((e = lineeditor_output_terminal_op (d, op, arg, NULL))
                    != ___FIX(___NO_ERR))
                  {
                    d->terminal_param_num = pn;
                    return e;
                  }
              }

            break;
          }
        }
    }

  d->terminal_param_num = pn;

  return ___FIX(___NO_ERR);
}
