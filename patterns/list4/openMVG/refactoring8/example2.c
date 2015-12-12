VL_INLINE T
VL_XCAT(_vl_vhsum_sse2_, SFX)(VTYPE x)
{
  T acc ;
#if (VSIZE == 4)
  {
    VTYPE sum ;
    VTYPE shuffle ;
    /* shuffle = [1 0 3 2] */
    /* sum     = [3+1 2+0 1+3 0+2] */
    /* shuffle = [2+0 3+1 0+2 1+3] */
    /* vacc    = [3+1+2+0 3+1+2+0 1+3+0+2 0+2+1+3] */
    shuffle = VSHU (x, x, _MM_SHUFFLE(1, 0, 3, 2)) ;
    sum     = VADD (x, shuffle) ;
    shuffle = VSHU (sum, sum, _MM_SHUFFLE(2, 3, 0, 1)) ;
    x       = VADD (sum, shuffle) ;
  }
#else
  {
    VTYPE shuffle ;
    /* acc     = [1   0  ] */
    /* shuffle = [0   1  ] */
    /* sum     = [1+0 0+1] */
    shuffle = VSHU (x, x, _MM_SHUFFLE2(0, 1)) ;
    x       = VADD (x, shuffle) ;
  }
#endif
  VST1(&acc, x);
  return acc ;
}
