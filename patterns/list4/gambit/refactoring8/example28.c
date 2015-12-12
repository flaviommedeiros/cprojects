___HIDDEN ___SCMOBJ ___device_tty_write_raw_virt
   ___P((___device_stream *self,
         ___U8 *buf,
         ___stream_index len,
         ___stream_index *len_done),
        (self,
         buf,
         len,
         len_done)
___device_stream *self;
___U8 *buf;
___stream_index len;
___stream_index *len_done;)
{
  ___device_tty *d = ___CAST(___device_tty*,self);
  ___SCMOBJ e;

  if ((e = ___device_tty_force_open (d)) != ___FIX(___NO_ERR))
    return e;

#ifdef USE_LINEEDITOR

  if (d->lineeditor_mode != LINEEDITOR_MODE_DISABLE)
    {
      if (!d->output_raw)
        {
          ___SCMOBJ e;
          ___U8 *byte_buf_end;
          int byte_buf_avail;

          if ((e = lineeditor_end_paren_balance (d))
               != ___FIX(___NO_ERR) ||
              (e = lineeditor_output_set_attrs (d, d->output_attrs))
              != ___FIX(___NO_ERR) ||
              (e = lineeditor_output_drain (d))
              != ___FIX(___NO_ERR))
            return e;

          byte_buf_end = buf + len;
          byte_buf_avail = len + d->output_char_incomplete;

          /* convert the bytes to characters */

          while (byte_buf_avail > 0)
            {
              ___C char_buf[128];
              int char_buf_avail = ___NBELEMS(char_buf);
              int orig_byte_buf_avail = byte_buf_avail;
              int code;

              code = chars_from_bytes (char_buf,
                                       &char_buf_avail,
                                       byte_buf_end - byte_buf_avail,
                                       &byte_buf_avail,
                                       &d->output_decoding_state);

              switch (code)
                {
                case ___CONVERSION_DONE:
                  if ((e = lineeditor_output
                             (d,
                              char_buf,
                              ___NBELEMS(char_buf) - char_buf_avail))
                      != ___FIX(___NO_ERR))
                    {
                      /*******************************/
                      return e;
                    }
                  lineeditor_output_drain (d); /* ignore error */
                  break;

                case ___INCOMPLETE_CHAR:
                  *len_done = byte_buf_avail - d->output_char_incomplete;
                  d->output_char_incomplete = byte_buf_avail;
                  return ___FIX(___NO_ERR);

                case ___ILLEGAL_CHAR:
                  /* ignore illegal characters */
                  break;
                }
            }

          *len_done = len;
          d->output_char_incomplete = 0;
          return ___FIX(___NO_ERR);
        }
    }

#endif

  return ___device_tty_write_raw_no_lineeditor (d, buf, len, len_done);
}
