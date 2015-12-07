#ifdef PARANOID
if (tagb == TW_NaN)
#endif /* PARANOID */
    {
      signalling = !(b->sigh & 0x40000000);
      x = b;
    }
#ifdef PARANOID
  else
    {
      signalling = 0;
      EXCEPTION(EX_INTERNAL|0x113);
      x = &CONST_QNaN;
    }
