if (bits_set || min > 0
#ifdef SUPPORT_JIT
    || (options & (PCRE_STUDY_JIT_COMPILE | PCRE_STUDY_JIT_PARTIAL_SOFT_COMPILE
                 | PCRE_STUDY_JIT_PARTIAL_HARD_COMPILE)) != 0
#endif
  )
  {
  extra = (PUBL(extra) *)(PUBL(malloc))
    (sizeof(PUBL(extra)) + sizeof(pcre_study_data));
  if (extra == NULL)
    {
    *errorptr = "failed to get memory";
    return NULL;
    }

  study = (pcre_study_data *)((char *)extra + sizeof(PUBL(extra)));
  extra->flags = PCRE_EXTRA_STUDY_DATA;
  extra->study_data = study;

  study->size = sizeof(pcre_study_data);
  study->flags = 0;

  /* Set the start bits always, to avoid unset memory errors if the
  study data is written to a file, but set the flag only if any of the bits
  are set, to save time looking when none are. */

  if (bits_set)
    {
    study->flags |= PCRE_STUDY_MAPPED;
    memcpy(study->start_bits, start_bits, sizeof(start_bits));
    }
  else memset(study->start_bits, 0, 32 * sizeof(pcre_uint8));

#ifdef PCRE_DEBUG
  if (bits_set)
    {
    pcre_uint8 *ptr = start_bits;
    int i;

    printf("Start bits:\n");
    for (i = 0; i < 32; i++)
      printf("%3d: %02x%s", i * 8, *ptr++, ((i + 1) & 0x7) != 0? " " : "\n");
    }
#endif

  /* Always set the minlength value in the block, because the JIT compiler
  makes use of it. However, don't set the bit unless the length is greater than
  zero - the interpretive pcre_exec() and pcre_dfa_exec() needn't waste time
  checking the zero case. */

  if (min > 0)
    {
    study->flags |= PCRE_STUDY_MINLEN;
    study->minlength = min;
    }
  else study->minlength = 0;

  /* If JIT support was compiled and requested, attempt the JIT compilation.
  If no starting bytes were found, and the minimum length is zero, and JIT
  compilation fails, abandon the extra block and return NULL. */

#ifdef SUPPORT_JIT
  extra->executable_jit = NULL;
  if ((options & PCRE_STUDY_JIT_COMPILE) != 0)
    PRIV(jit_compile)(re, extra, JIT_COMPILE);
  if ((options & PCRE_STUDY_JIT_PARTIAL_SOFT_COMPILE) != 0)
    PRIV(jit_compile)(re, extra, JIT_PARTIAL_SOFT_COMPILE);
  if ((options & PCRE_STUDY_JIT_PARTIAL_HARD_COMPILE) != 0)
    PRIV(jit_compile)(re, extra, JIT_PARTIAL_HARD_COMPILE);

  if (study->flags == 0 && (extra->flags & PCRE_EXTRA_EXECUTABLE_JIT) == 0)
    {
#ifdef COMPILE_PCRE8
    pcre_free_study(extra);
#endif
#ifdef COMPILE_PCRE16
    pcre16_free_study(extra);
#endif
    extra = NULL;
    }
#endif
  }
