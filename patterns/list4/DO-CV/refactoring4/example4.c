#if defined(PNG_USER_MEM_SUPPORTED) && PNG_DEBUG
if (ierror == 0)
      fprintf(STDERR, " libpng passes test\n");

   else
      fprintf(STDERR, " libpng FAILS test\n");
