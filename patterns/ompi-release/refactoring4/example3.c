# if defined(__ia64__)
if (!strncmp("itc MHz", line, 7))
# else
      if (!strncmp("cpu MHz", line, 7))
# endif
      {
	strtok(line, ":");
      
	vt_ticks_per_sec =
	  strtol((char*) strtok(NULL, " \n"), (char**) NULL, 0) * 1000000LL;
      }
      else if (!strncmp("timebase", line, 8))
      {
	strtok(line, ":");
      
	vt_ticks_per_sec =
	  strtol((char*) strtok(NULL, " \n"), (char**) NULL, 0);
      }
