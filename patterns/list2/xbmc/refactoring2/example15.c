#ifdef PNG_ERROR_NUMBERS_SUPPORTED
if (png_ptr->flags&
     (PNG_FLAG_STRIP_ERROR_NUMBERS|PNG_FLAG_STRIP_ERROR_TEXT))
#endif
     {
       if (*warning_message == '#')
       {
           for (offset=1; offset<15; offset++)
              if (*(warning_message+offset) == ' ')
                  break;
       }
     }
