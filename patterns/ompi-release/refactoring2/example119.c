#ifdef VT_DYNINST
if( !vt_dyn_attaching )
#endif /* VT_DYNINST */
  {
    if( ret != -1 )
      vt_fork(ret);
  }
