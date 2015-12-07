#if defined (__MSDOS__)
if (string[i] == '/' || string[i] == '\\' /* || !string[i] */)
#else
      if (string[i] == '/' /* || !string[i] */)
#endif
	break;
