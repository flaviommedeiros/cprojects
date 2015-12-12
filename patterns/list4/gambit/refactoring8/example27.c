___HIDDEN ___SCMOBJ lineeditor_delete_chars
   ___P((___device_tty *self,
         int pos,
         ___BOOL copy_to_clipboard),
        (self,
         pos,
         copy_to_clipboard)
___device_tty *self;
int pos;
___BOOL copy_to_clipboard;)
{
  ___device_tty *d = self;

#if 1

  return lineeditor_delete_then_insert_chars
           (d,
            pos,
            copy_to_clipboard,
            NULL,
            0);

#else

  ___SCMOBJ e;
  extensible_string *edited = &d->current.hist->edited;
  int start;
  int end;
  int n;

  if (pos < 0 ||
      pos > edited->length)
    return ___FIX(___INVALID_OP_ERR);

  if (pos < d->current.edit_point)
    {
      start = pos;
      end = d->current.edit_point;
    }
  else
    {
      start = d->current.edit_point;
      end = pos;
    }

  n = end - start;

  if (n == 0)
    return ___FIX(___NO_ERR);

  if (copy_to_clipboard &&
      ((e = lineeditor_copy_to_clipboard (d, &edited->buffer[start], n))
       != ___FIX(___NO_ERR)))
    return e;

  extensible_string_delete (edited, start, n);

  if (d->current.mark_point >= start)
    {
      if (d->current.mark_point >= end)
        d->current.mark_point -= n;
      else
        d->current.mark_point = start;
    }

  if ((e = lineeditor_update_region (d, start, edited->length + n))
      != ___FIX(___NO_ERR))
    return e;

  return lineeditor_move_edit_point (d, start);
#endif
}
