static char *type[] = {
     "char",
     "short",
     "int",
     "long",
     "unsigned",
     #ifdef NO_FLOATS
     "signed",
     "signed",
	 #else
     "float",
     "double"
	 #endif
   };
