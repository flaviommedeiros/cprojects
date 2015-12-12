#  ifdef PNG_ERROR_NUMBERS_SUPPORTED
if (*warning_message == PNG_LITERAL_SHARP)
   {
     int offset;
     char warning_number[16];
     for (offset = 0; offset < 15; offset++)
     {
        warning_number[offset] = warning_message[offset + 1];
        if (warning_message[offset] == ' ')
            break;
     }
     if ((offset > 1) && (offset < 15))
     {
       warning_number[offset + 1] = '\0';
       fprintf(stderr, "libpng warning no. %s: %s",
          warning_number, warning_message + offset);
       fprintf(stderr, PNG_STRING_NEWLINE);
     }
     else
     {
       fprintf(stderr, "libpng warning: %s",
          warning_message);
       fprintf(stderr, PNG_STRING_NEWLINE);
     }
   }
   else
#  endif
   {
     fprintf(stderr, "libpng warning: %s", warning_message);
     fprintf(stderr, PNG_STRING_NEWLINE);
   }
