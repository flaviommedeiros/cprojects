switch (ev->event_kind)
    {
    case LINEEDITOR_EV_NONE:
      return ___FIX(___NO_ERR);

    case LINEEDITOR_EV_KEY:
      if (ev->event_char < ___UNICODE_SPACE || /* discard control characters */
          ev->event_char == ___UNICODE_RUBOUT)
        return ___FIX(___INVALID_OP_ERR);
      return lineeditor_insert_chars (d, &ev->event_char, 1);

    case LINEEDITOR_EV_RETURN:
      return lineeditor_line_done (d, 0);

    case LINEEDITOR_EV_BACK:
      return lineeditor_delete_chars (d, d->current.edit_point-1, 0);

    case LINEEDITOR_EV_BACK_WORD:
    case LINEEDITOR_EV_BACK_SEXPR:
      {
        int i;
        int dir = (ev->event_kind == LINEEDITOR_EV_BACK_WORD)
                  ? BACK_WORD
                  : BACK_SEXPR;
        if (!lineeditor_word_boundary (d, dir, d->current.edit_point, &i))
          return ___FIX(___INVALID_OP_ERR);
        return lineeditor_delete_chars (d, i, 1);
      }

    case LINEEDITOR_EV_TAB:
      return lineeditor_word_completion (d);

    case LINEEDITOR_EV_MARK:
      d->current.mark_point = d->current.edit_point;
      return ___FIX(___NO_ERR);

    case LINEEDITOR_EV_PASTE:
      return lineeditor_paste_from_clipboard (d);

    case LINEEDITOR_EV_CUT:
      return lineeditor_delete_chars (d, d->current.mark_point, 1);

    case LINEEDITOR_EV_CUT_RIGHT:
      return lineeditor_delete_chars (d, edited->length, 1);

    case LINEEDITOR_EV_CUT_LEFT:
      return lineeditor_delete_chars (d, 0, 1);

    case LINEEDITOR_EV_REFRESH:
      return lineeditor_refresh (d);

    case LINEEDITOR_EV_TRANSPOSE:
      {
        int i = d->current.edit_point;
        if (i <= 0 ||
            edited->length < 2)
          return ___FIX(___INVALID_OP_ERR);
        if (i == edited->length)
          return lineeditor_transpose_chars (d, i-2, i-1, i-1, i);
        else
          return lineeditor_transpose_chars (d, i-1, i, i, i+1);
      }

    case LINEEDITOR_EV_TRANSPOSE_WORD:
    case LINEEDITOR_EV_TRANSPOSE_SEXPR:
      {
        int start1;
        int end1;
        int start2;
        int end2;
        int dir = (ev->event_kind == LINEEDITOR_EV_TRANSPOSE_WORD)
                  ? FORW_WORD
                  : FORW_SEXPR;
        if (!lineeditor_word_boundary (d, dir, d->current.edit_point, &end2) ||
            !lineeditor_word_boundary (d, dir+1, end2, &start2) ||
            !lineeditor_word_boundary (d, dir+1, start2, &start1) ||
            !lineeditor_word_boundary (d, dir, start1, &end1))
          return ___FIX(___INVALID_OP_ERR);
        return lineeditor_transpose_chars (d, start1, end1, start2, end2);
      }

    case LINEEDITOR_EV_UP:
      return lineeditor_move_history_relative (d, 1);

    case LINEEDITOR_EV_DOWN:
      return lineeditor_move_history_relative (d, 0);

    case LINEEDITOR_EV_RIGHT:
      return lineeditor_move_edit_point (d, d->current.edit_point+1);

    case LINEEDITOR_EV_RIGHT_WORD:
    case LINEEDITOR_EV_RIGHT_SEXPR:
      {
        int i;
        int dir = (ev->event_kind == LINEEDITOR_EV_RIGHT_WORD)
                  ? FORW_WORD
                  : FORW_SEXPR;
        lineeditor_word_boundary (d, dir, d->current.edit_point, &i);
        return lineeditor_move_edit_point (d, i);
      }

    case LINEEDITOR_EV_LEFT:
      return lineeditor_move_edit_point (d, d->current.edit_point-1);

    case LINEEDITOR_EV_LEFT_WORD:
    case LINEEDITOR_EV_LEFT_SEXPR:
      {
        int i;
        int dir = (ev->event_kind == LINEEDITOR_EV_LEFT_WORD)
                  ? BACK_WORD
                  : BACK_SEXPR;
        lineeditor_word_boundary (d, dir, d->current.edit_point, &i);
        return lineeditor_move_edit_point (d, i);
      }

    case LINEEDITOR_EV_HOME:
      return lineeditor_move_edit_point (d, 0);

    case LINEEDITOR_EV_HOME_DOC:
      return lineeditor_move_history (d, d->hist_last->next);

    case LINEEDITOR_EV_INSERT:
      return ___FIX(___INVALID_OP_ERR);

    case LINEEDITOR_EV_DELETE:
      if (edited->length == 0)
        return lineeditor_line_done (d, 1);
      else
        return lineeditor_delete_chars (d, d->current.edit_point+1, 0);

    case LINEEDITOR_EV_DELETE_WORD:
    case LINEEDITOR_EV_DELETE_SEXPR:
      {
        int i;
        int dir = (ev->event_kind == LINEEDITOR_EV_DELETE_WORD)
                  ? FORW_WORD
                  : FORW_SEXPR;
        if (!lineeditor_word_boundary (d, dir, d->current.edit_point, &i))
          return ___FIX(___INVALID_OP_ERR);
        return lineeditor_delete_chars (d, i, 1);
      }

    case LINEEDITOR_EV_END:
      return lineeditor_move_edit_point (d, edited->length);

    case LINEEDITOR_EV_END_DOC:
      return lineeditor_move_history (d, d->hist_last);

    case LINEEDITOR_EV_F1:
    case LINEEDITOR_EV_META_F1:
    case LINEEDITOR_EV_F2:
    case LINEEDITOR_EV_META_F2:
    case LINEEDITOR_EV_F3:
    case LINEEDITOR_EV_META_F3:
    case LINEEDITOR_EV_F4:
    case LINEEDITOR_EV_META_F4:
#ifdef LINEEDITOR_SUPPORT_F5_TO_F12
    case LINEEDITOR_EV_F5:
    case LINEEDITOR_EV_META_F5:
    case LINEEDITOR_EV_F6:
    case LINEEDITOR_EV_META_F6:
    case LINEEDITOR_EV_F7:
    case LINEEDITOR_EV_META_F7:
    case LINEEDITOR_EV_F8:
    case LINEEDITOR_EV_META_F8:
    case LINEEDITOR_EV_F9:
    case LINEEDITOR_EV_META_F9:
    case LINEEDITOR_EV_F10:
    case LINEEDITOR_EV_META_F10:
    case LINEEDITOR_EV_F11:
    case LINEEDITOR_EV_META_F11:
    case LINEEDITOR_EV_F12:
    case LINEEDITOR_EV_META_F12:
#endif
      {
        ___C command[7];
        command[0] = ___UNICODE_SHARP;
        command[1] = ___UNICODE_VBAR;
        command[2] = ___UNICODE_VBAR;
        command[3] = ___UNICODE_SHARP;
        command[4] = ___UNICODE_COMMA;
        switch (ev->event_kind)
          {
#ifdef LINEEDITOR_SUPPORT_F5_TO_F12
          case LINEEDITOR_EV_F8:
            command[5] = ___UNICODE_LOWER_C;
            break;
          case LINEEDITOR_EV_F9:
            command[5] = ___UNICODE_MINUS;
            break;
          case LINEEDITOR_EV_F10:
            command[5] = ___UNICODE_PLUS;
            break;
          case LINEEDITOR_EV_F11:
            command[5] = ___UNICODE_LOWER_S;
            break;
          case LINEEDITOR_EV_F12:
            command[5] = ___UNICODE_LOWER_L;
            break;
#endif
          default:
            command[5] = ___UNICODE_LOWER_T;
            break;
          }
        command[6] = ___UNICODE_SEMICOLON;
        if (lineeditor_move_edit_point (d, 0)
            == ___FIX(___NO_ERR) &&
            lineeditor_delete_chars (d, edited->length, 0)
            == ___FIX(___NO_ERR) &&
            lineeditor_insert_chars (d, command, 7)
            == ___FIX(___NO_ERR))
          return lineeditor_line_done (d, 0);
        break;
      }
    }
