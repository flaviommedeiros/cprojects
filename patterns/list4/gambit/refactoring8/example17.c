___HIDDEN ___WORD alloc_scmobj_perm
   ___P((int subtype,
         ___SIZE_TS bytes),
        (subtype,
         bytes)
int subtype;
___SIZE_TS bytes;)
{
  void *ptr;
  ___WORD *base;
  ___SIZE_TS words = ___PERM_BODY_OFS + ___WORDS(bytes);

  /*
   * Some objects, such as ___sFOREIGN, ___sS64VECTOR, ___sU64VECTOR,
   * ___sF64VECTOR, ___sFLONUM and ___sBIGNUM, must have a body that
   * is aligned on a multiple of 8 on some machines.  Here, we force
   * alignment to a multiple of 8 even if not necessary in all cases
   * because it is typically more efficient due to a better
   * utilization of the cache.
   */

  ptr = alloc_mem_aligned_perm (words,
                                8>>___LWS,
                                (-___PERM_BODY_OFS)&((8>>___LWS)-1));

  if (ptr == 0)
    return ___FIX(___HEAP_OVERFLOW_ERR);

  base = ___CAST(___WORD*,ptr);

#ifdef ___USE_HANDLES
  base[___PERM_HAND_OFS] = ___CAST(___WORD,base+___PERM_BODY_OFS-___BODY_OFS);
#endif
  base[___PERM_BODY_OFS-1] = ___MAKE_HD(bytes, subtype, ___PERM);

  return ___TAG((base + ___PERM_HAND_OFS - ___BODY_OFS),
                (subtype == ___sPAIR ? ___tPAIR : ___tSUBTYPED));
}
