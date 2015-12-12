#if defined(USE_XSHM)
if (!useXshm)
#endif
    {
      free(addr);
      return;
    }
