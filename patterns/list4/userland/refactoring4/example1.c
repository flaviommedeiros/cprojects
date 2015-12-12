#ifdef MSDOS
if ((fin=fopen(name, "rb"))==NULL)
#else
      if ((fin=fopen(name, "r"))==NULL)
#endif
      {
            perror(name);
            return Error_;
      }
