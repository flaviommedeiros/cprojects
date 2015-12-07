#ifdef PNG_ERROR_NUMBERS_SUPPORTED
if (*error_message == '#')
   {
     int offset;
     char error_number[16];
     for (offset=0; offset<15; offset++)
     {
         error_number[offset] = *(error_message+offset+1);
         if (*(error_message+offset) == ' ')
             break;
     }
     if((offset > 1) && (offset < 15))
     {
       error_number[offset-1]='\0';
       fprintf(stderr, "libpng error no. %s: %s\n", error_number,
          error_message+offset);
     }
     else
       fprintf(stderr, "libpng error: %s, offset=%d\n", error_message,offset);
   }
   else
#endif
   fprintf(stderr, "libpng error: %s\n", error_message);
