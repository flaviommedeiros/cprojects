switch (op)
    {
    case TERMINAL_NOOP:
      break;

    case TERMINAL_CTRL - ___UNICODE_BELL:
      {
#ifdef USE_POSIX

        {
          ___C c = ___UNICODE_BELL;
          e = lineeditor_output (d, &c, 1);
        }

#endif

#ifdef USE_WIN32

        if (!MessageBeep (MB_OK))
          e = err_code_from_GetLastError ();

#endif

        break;
      }

    case TERMINAL_CTRL - ___UNICODE_BACKSPACE:
      {
        if (d->terminal_col > 0)
          d->terminal_col--;
        else if (d->terminal_row > 0 && d->has_auto_left_margin)
          {
            d->terminal_row--;
            d->terminal_col = d->terminal_nb_cols - 1;
          }

        d->terminal_cursor = d->terminal_row * d->terminal_nb_cols +
                             d->terminal_col;

        d->terminal_delayed_wrap = 0;

#ifdef USE_POSIX

        {
          ___C c = ___UNICODE_BACKSPACE;
          e = lineeditor_output (d, &c, 1);
        }

#endif

#ifdef USE_WIN32

        {
          CONSOLE_SCREEN_BUFFER_INFO info;

          if (!GetConsoleScreenBufferInfo (d->hout, &info))
            e = err_code_from_GetLastError ();
          else
            {
              COORD pos = info.dwCursorPosition;

              if (pos.X > 0)
                pos.X--;
              else if (pos.Y > info.srWindow.Top && d->has_auto_left_margin)
                {
                  pos.X = info.dwSize.X - 1;
                  pos.Y--;
                }

              if (!SetConsoleCursorPosition (d->hout, pos))
                e = err_code_from_GetLastError ();
            }
        }

#endif

        break;
      }

    case TERMINAL_CTRL - ___UNICODE_TAB:
      {
        e = lineeditor_output_terminal_op_move_col
              (d,
               8 - d->terminal_col % 8);
        break;
      }

    case TERMINAL_CTRL - ___UNICODE_LINEFEED:
      {
        if (d->terminal_row < d->terminal_nb_rows-1)
          d->terminal_row++;
        else
          d->current.line_start -= d->terminal_nb_cols;

        if (d->linefeed_moves_to_left_margin || !d->output_raw)
          d->terminal_col = 0;

        d->terminal_cursor = d->terminal_row * d->terminal_nb_cols +
                             d->terminal_col;

        d->terminal_delayed_wrap = 0;

#ifdef USE_POSIX

        {
          ___C c = ___UNICODE_LINEFEED;
          e = lineeditor_output (d, &c, 1);
        }

#endif

#ifdef USE_WIN32

        {
          CONSOLE_SCREEN_BUFFER_INFO info;

          if (!GetConsoleScreenBufferInfo (d->hout, &info))
            e = err_code_from_GetLastError ();
          else
            {
              COORD pos = info.dwCursorPosition;

              if (pos.Y >= info.dwSize.Y - 1)
                {
                  SMALL_RECT rect;
                  CHAR_INFO fill;
                  COORD dest;

                  rect.Top = 0;
                  rect.Bottom = info.dwSize.Y - 1;
                  rect.Left = 0;
                  rect.Right = info.dwSize.X - 1;

                  dest.X = 0;
                  dest.Y = -1;

                  fill.Attributes = info.wAttributes;
                  TTY_CHAR_SELECT(fill.Char.AsciiChar = ' ',
                                  fill.Char.UnicodeChar = ' ');

                  if (!ScrollConsoleScreenBuffer (d->hout,
                                                  &rect,
                                                  &rect,
                                                  dest,
                                                  &fill))
                    e = err_code_from_GetLastError ();

                  pos.Y = info.dwSize.Y - 1;
                }
              else
                pos.Y++;

              if (e == ___FIX(___NO_ERR))
                {
                  if (d->linefeed_moves_to_left_margin || !d->output_raw)
                    pos.X = 0;

                  if (!SetConsoleCursorPosition (d->hout, pos))
                    e = err_code_from_GetLastError ();
                }
            }
        }

#endif

        break;
      }

    case TERMINAL_CTRL - ___UNICODE_RETURN:
      {
        d->terminal_col = 0;
        d->terminal_cursor = d->terminal_row * d->terminal_nb_cols;
        d->terminal_delayed_wrap = 0;

#ifdef USE_POSIX

        {
          ___C c = ___UNICODE_RETURN;
          e = lineeditor_output (d, &c, 1);
        }

#endif

#ifdef USE_WIN32

        {
          CONSOLE_SCREEN_BUFFER_INFO info;

          if (!GetConsoleScreenBufferInfo (d->hout, &info))
            e = err_code_from_GetLastError ();
          else
            {
              COORD pos = info.dwCursorPosition;

              pos.X = 0;

              if (!SetConsoleCursorPosition (d->hout, pos))
                e = err_code_from_GetLastError ();
            }
        }

#endif

        break;
      }

    case TERMINAL_SET_ATTRS:
      {
#ifdef USE_POSIX

        e = lineeditor_output_set_attrs (d, arg);

#endif

#ifdef USE_WIN32

        {
          int style = GET_STYLE(arg);
          int fg = GET_FOREGROUND_COLOR(arg);
          int bg = GET_BACKGROUND_COLOR(arg);
          WORD default_attr = d->hout_initial_info.wAttributes;
          WORD attr = 0;

          if (fg == DEFAULT_TEXT_COLOR)
            {
              fg = (default_attr & FOREGROUND_BLUE  ? 4 : 0) +
                   (default_attr & FOREGROUND_GREEN ? 2 : 0) +
                   (default_attr & FOREGROUND_RED   ? 1 : 0);
              if ((default_attr & FOREGROUND_INTENSITY) == 0)
                style ^= TEXT_STYLE_BOLD;
            }

          if (bg == DEFAULT_TEXT_COLOR)
            {
              bg = (default_attr & BACKGROUND_BLUE  ? 4 : 0) +
                   (default_attr & BACKGROUND_GREEN ? 2 : 0) +
                   (default_attr & BACKGROUND_RED   ? 1 : 0);
              if ((default_attr & BACKGROUND_INTENSITY) == 0)
                style ^= TEXT_STYLE_UNDERLINE;
            }

          if ((style & TEXT_STYLE_BOLD) == 0)
            attr |= FOREGROUND_INTENSITY;

          if ((style & TEXT_STYLE_UNDERLINE) == 0)
            attr |= BACKGROUND_INTENSITY;

          if (style & TEXT_STYLE_REVERSE)
            {
              int temp = fg;
              fg = bg;
              bg = temp;
            }

          if (fg & 4) attr |= FOREGROUND_BLUE;
          if (fg & 2) attr |= FOREGROUND_GREEN;
          if (fg & 1) attr |= FOREGROUND_RED;
          if (bg & 4) attr |= BACKGROUND_BLUE;
          if (bg & 2) attr |= BACKGROUND_GREEN;
          if (bg & 1) attr |= BACKGROUND_RED;

          if (!SetConsoleTextAttribute (d->hout, attr))
            e = err_code_from_GetLastError ();
        }

#endif

        break;
      }

#ifdef USE_WIN32

    case TERMINAL_ERASE_DISP:
    case TERMINAL_ERASE_LINE:
      {
        if (arg <= 2) /* argument valid? */
          {
            COORD pos;
            CONSOLE_SCREEN_BUFFER_INFO info;
            DWORD n;
            DWORD written;

            if (!GetConsoleScreenBufferInfo (d->hout, &info))
              return err_code_from_GetLastError ();

            if (d->terminal_col == 0 &&
                d->terminal_row == 0)
              {
                pos.X = 0;
                pos.Y = 0;

                if (!SetConsoleCursorPosition (d->hout, pos))
                  return err_code_from_GetLastError ();
              }
            else
              pos = info.dwCursorPosition;

            if (arg == 0)
              n = info.dwSize.X - pos.X;
            else
              {
                if (arg == 1)
                  n = pos.X;
                else
                  n = info.dwSize.X;
                pos.X = 0;
              }

            if (op == TERMINAL_ERASE_DISP)
              {
                if (arg == 0)
                  n += info.dwSize.X * (info.dwSize.Y - pos.Y - 1);
                else
                  {
                    if (arg == 1)
                      n += info.dwSize.X * pos.Y;
                    else
                      n = info.dwSize.X * info.dwSize.Y;
                    pos.Y = 0;
                  }
              }

            if (!FillConsoleOutputAttribute
                   (d->hout,
                    info.wAttributes,
                    n,
                    pos,
                    &written) ||
                !FillConsoleOutputCharacter
                   (d->hout,
                    ' ',
                    n,
                    pos,
                    &written))
              e = err_code_from_GetLastError ();
          }

        break;
      }

    case TERMINAL_WINDOW_OP:
      {
        int window_op = arg & ((1<<8)-1);
        int arg1 = (arg >> 8) & ((1<<12)-1);
        int arg2 = (arg >> 20) & ((1<<12)-1);
        HWND cons_wind = GetConsoleWindow ();

        if (cons_wind != NULL)
          {
            if (text_arg != NULL)
              {
                SetWindowTextA (cons_wind,
                                ___CAST(LPCSTR,text_arg)); /* ignore error */
              }
            else
              {
                switch (window_op)
                  {
                  case 1: /* De-iconify window */
                  case 2: /* Iconify window */
                    ShowWindow (cons_wind,
                                (window_op == 1) ? SW_RESTORE : SW_MINIMIZE);
                    break;

                  case 3: /* Move window to [arg1, arg2] */
                    SetWindowPos (cons_wind,
                                  cons_wind,
                                  arg1,
                                  arg2,
                                  0,
                                  0,
                                  SWP_NOZORDER | SWP_NOSIZE);
                    break;

                  case 4: /* Resize window to height=arg1 and width=arg2 in pixels */
                    SetWindowPos (cons_wind,
                                  cons_wind,
                                  0,
                                  0,
                                  arg2,
                                  arg1,
                                  SWP_NOZORDER | SWP_NOMOVE);
                    break;

                  case 5: /* Raise the window to the front of the stacking order */
                  case 6: /* Lower the window to the bottom of the stacking order */
                    SetWindowPos (cons_wind,
                                  (window_op == 5) ? HWND_TOP : HWND_BOTTOM,
                                  0,
                                  0,
                                  0,
                                  0,
                                  SWP_NOSIZE | SWP_NOMOVE);
                    break;

                  case 7: /* Refresh the window */
                    break;

                  case 8: /* Resize window to height=arg1 and width=arg2 in chars */
                    break;

                  case 9: /* Maximize or un-maximize window (arg1=0 or arg1=1) */
                    ShowWindow (cons_wind,
                                (arg1 == 0) ? SW_MAXIMIZE : SW_RESTORE);
                    break;
                  }
              }
          }

        break;
      }

#else

    case TERMINAL_ERASE_DISP:
      {
        switch (arg)
          {
          case 1: /* erase from beginning of screen */
            break;
          case 2: /* erase all screen */
            if (d->terminal_col != 0 || d->terminal_row != 0)
              break;
          case 0: /* erase to end of screen */
            e = lineeditor_output_cap0 (d, LINEEDITOR_CAP_ED, 1);
            break;
          }
        break;
      }

    case TERMINAL_ERASE_LINE:
      {
        switch (arg)
          {
          case 1: /* erase from beginning of line */
            e = lineeditor_output_cap0 (d, LINEEDITOR_CAP_EL1, 1);
            break;
          case 2: /* erase all line */
            if (d->terminal_col != 0)
              break;
          case 0: /* erase to end of line */
            e = lineeditor_output_cap0 (d, LINEEDITOR_CAP_EL, 1);
            break;
          }
        break;
      }

    case TERMINAL_WINDOW_OP:
      {
        int window_op = arg & ((1<<8)-1);
        int arg1 = (arg >> 8) & ((1<<12)-1);
        int arg2 = (arg >> 20) & ((1<<12)-1);

        if (text_arg != NULL)
          {
            ___C c;

            e = lineeditor_output_cap1
                  (d,
                   LINEEDITOR_CAP_WINDOW_OP3,
                   window_op,
                   1);

            while (e == ___FIX(___NO_ERR) &&
                   *text_arg != ___UNICODE_NUL)
              {
                c = *text_arg++;
                e = lineeditor_output (d, &c, 1);
              }

            if (e == ___FIX(___NO_ERR))
              {
                c = ___UNICODE_BELL;
                e = lineeditor_output (d, &c, 1);
              }
          }
        else
          {
            switch (window_op)
              {
              case 1: /* De-iconify window */
              case 2: /* Iconify window */
              case 5: /* Raise the window to the front of the stacking order */
              case 6: /* Lower the window to the bottom of the stacking order */
              case 7: /* Refresh the window */
                e = lineeditor_output_cap1
                      (d,
                       LINEEDITOR_CAP_WINDOW_OP0,
                       window_op,
                       1);
                break;

              case 9: /* Maximize or un-maximize window (arg1=0 or arg1=1) */
                e = lineeditor_output_cap2
                      (d,
                       LINEEDITOR_CAP_WINDOW_OP1,
                       window_op,
                       arg1,
                       1);
                break;

              case 3: /* Move window to [arg1, arg2] */
              case 4: /* Resize window to height=arg1 and width=arg2 in pixels */
              case 8: /* Resize window to height=arg1 and width=arg2 in chars */
                e = lineeditor_output_cap3
                      (d,
                       LINEEDITOR_CAP_WINDOW_OP2,
                       window_op,
                       arg1,
                       arg2,
                       1);
                break;
              }
          }

        break;
      }

#endif

    case TERMINAL_MOVE_COL:
      {
        e = lineeditor_output_terminal_op_move_col (d, arg);
        break;
      }

    case TERMINAL_MOVE_ROW:
      {
        e = lineeditor_output_terminal_op_move_row (d, arg);
        break;
      }

    default:
      {
        if (op >= TERMINAL_MOVE_ABS)
          e = lineeditor_output_terminal_op_move_abs
                (d,
                 arg,
                 op - TERMINAL_MOVE_ABS);
        break;
      }
    }
