#ifndef USE_LINEEDITOR
if (!d->input_raw)
          hin_mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
        else
#endif
          hin_mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
