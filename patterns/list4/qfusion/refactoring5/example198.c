#ifdef PNG_ERROR_NUMBERS_SUPPORTED
if (*error_message == PNG_LITERAL_SHARP)
   {
     /* Strip "#nnnn " from beginning of error message. */
     int offset;
     char error_number[16];
     for (offset = 0; offset<15; offset++)
     {
         error_number[offset] = error_message[offset + 1];
         if (error_message[offset] == ' ')
             break;
     }
     if ((offset > 1) && (offset < 15))
     {
       error_number[offset - 1] = '\0';
       fprintf(stderr, "libpng error no. %s: %s",
          error_number, error_message + offset + 1);
       fprintf(stderr, PNG_STRING_NEWLINE);
     }
     else
     {
       fprintf(stderr, "libpng error: %s, offset=%d",
          error_message, offset);
       fprintf(stderr, PNG_STRING_NEWLINE);
     }
   }
   else
#endif
   {
      fprintf(stderr, "libpng error: %s", error_message);
      fprintf(stderr, PNG_STRING_NEWLINE);
   }
