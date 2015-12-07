#ifdef EVMSERR
if (errnoval == evmserr.value)
	msg = evmserr.msg;
      else
#endif
      /* Out of range, just return NULL */
      msg = NULL;
