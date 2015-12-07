#ifdef EVMSERR
if (errnoval == evmserr.value)
	name = evmserr.name;
      else
#endif
      /* Out of range, just return NULL */
      name = NULL;
