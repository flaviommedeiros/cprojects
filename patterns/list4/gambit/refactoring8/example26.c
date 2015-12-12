___HIDDEN ___SCMOBJ lineeditor_insert_chars
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
  ___device_tty *d = self;

#if 1

  if (len > 0)
    return lineeditor_delete_then_insert_chars
             (d,
              d->current.edit_point,
              0,
              buf,
              len);

  return ___FIX(___NO_ERR);

#else

  ___SCMOBJ e;
  extensible_string *edited = &d->current.hist->edited;
  int edit_point = d->current.edit_point;
  int open_paren_point;
  ___C c;

  if (len <= 0)
    return ___FIX(___NO_ERR);

  if ((e = extensible_string_insert (edited, edit_point, len, buf))
      != ___FIX(___NO_ERR))
    return e;

  if (d->current.mark_point > edit_point)
    d->current.mark_point += len;

  if ((e = lineeditor_update_region (d, edit_point, edited->length))
      != ___FIX(___NO_ERR))
    return e;

  edit_point += len;

  if (d->paren_balance_duration_nsecs > 0 &&
      !lineeditor_read_ready (d) &&
      (c = buf[len-1], CLOSE_PAREN(c)) &&
      lineeditor_word_boundary (d, BACK_SEXPR_PAREN, edit_point, &open_paren_point) &&
      (c = edited->buffer[open_paren_point], OPEN_PAREN(c)))
    {
      if ((e = lineeditor_move_edit_point (d, open_paren_point))
          != ___FIX(___NO_ERR))
        return e;

      lineeditor_output_drain (d); /* ignore error */

      d->current.edit_point = edit_point;
      d->current.completion_point = edit_point;
      d->current.paren_balance_trigger = 1;

      return ___FIX(___NO_ERR);
    }

  return lineeditor_move_edit_point (d, edit_point);
#endif
}
