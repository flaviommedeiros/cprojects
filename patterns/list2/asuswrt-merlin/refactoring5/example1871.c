#ifdef HAVE_LONG_LONG_TYPE
if((vto[i].flags & FLAGS_LONGLONG) && (vto[i].flags & FLAGS_UNSIGNED))
        vto[i].data.num.as_unsigned =
          (mp_uintmax_t)va_arg(arglist, mp_uintmax_t);
      else if(vto[i].flags & FLAGS_LONGLONG)
        vto[i].data.num.as_signed =
          (mp_intmax_t)va_arg(arglist, mp_intmax_t);
      else
#endif
      {
        if((vto[i].flags & FLAGS_LONG) && (vto[i].flags & FLAGS_UNSIGNED))
          vto[i].data.num.as_unsigned =
            (mp_uintmax_t)va_arg(arglist, unsigned long);
        else if(vto[i].flags & FLAGS_LONG)
          vto[i].data.num.as_signed =
            (mp_intmax_t)va_arg(arglist, long);
        else if(vto[i].flags & FLAGS_UNSIGNED)
          vto[i].data.num.as_unsigned =
            (mp_uintmax_t)va_arg(arglist, unsigned int);
        else
          vto[i].data.num.as_signed =
            (mp_intmax_t)va_arg(arglist, int);
      }
