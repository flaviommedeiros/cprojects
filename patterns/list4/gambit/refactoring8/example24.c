___HIDDEN ___SCMOBJ lineeditor_output_drain
   ___P((___device_tty *self),
        (self)
___device_tty *self;)
{
  /*
   * This routine drains the output buffers.  The return value is
   * ___FIX(___NO_ERR) if and only if the output buffers were
   * completely drained.  The return value is different from
   * ___FIX(___NO_ERR) only when ___device_tty_write
   * returned an error.
   */

  ___device_tty *d = self;
  ___SCMOBJ e;

  for (;;)
    {
      int byte_avail;
      int len = d->output_byte_hi - d->output_byte_lo;

      while (len > 0)
        {
          ___stream_index len_done;
          ___U8 *byte_buf = d->output_byte + d->output_byte_lo;

          if ((e = ___device_tty_write
                     (d,
                      byte_buf,
                      len,
                      &len_done)) != ___FIX(___NO_ERR))
            return e;

          len = d->output_byte_hi - (d->output_byte_lo += len_done);
        }

      d->output_byte_lo = 0;
      d->output_byte_hi = 0;

      len = d->output_char.length - d->output_char_lo;

      if (len <= 0)
        break;

      do
        {
          ___C *char_buf = d->output_char.buffer + d->output_char_lo;
          ___U8 *byte_buf = d->output_byte + d->output_byte_hi;

          byte_avail = ___NBELEMS(d->output_byte) - d->output_byte_hi;

          if (chars_to_bytes (char_buf,
                              &len,
                              byte_buf,
                              &byte_avail,
                              &d->output_encoding_state)
              == ___ILLEGAL_CHAR)
            len--; /* skip over the illegal character */

#ifdef ___DEBUG_TTY

          {
            int i;
            int n = (___NBELEMS(d->output_byte) - d->output_byte_hi) - byte_avail;

            ___printf ("lineeditor_output_drain  nb_bytes: %d ", n);

            for (i=0; i<n; i++)
              ___printf (" %02x", d->output_byte[i]);

            ___printf ("\n");
          }

#endif

          d->output_char_lo = d->output_char.length - len;

          d->output_byte_hi = ___NBELEMS(d->output_byte) - byte_avail;
        } while (byte_avail > 0 && len > 0);

      if (len <= 0)
        {
          extensible_string_set_length
            (&d->output_char, 0, 1); /* ignore error */
          d->output_char.length = 0; /* in case set_length failed */
          d->output_char_lo = 0;
        }
    }

  return ___FIX(___NO_ERR);
}
