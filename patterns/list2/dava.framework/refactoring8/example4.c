TRIO_PRIVATE BOOLEAN_T
TrioReadWideString
TRIO_ARGS4((self, target, flags, width),
	   trio_class_t *self,
	   trio_wchar_t *target,
	   trio_flags_t flags,
	   int width)
{
  int i;
  int size;
  
  assert(VALID(self));
  assert(VALID(self->InStream));

  TrioSkipWhitespaces(self);

#if defined(TRIO_COMPILER_SUPPORTS_MULTIBYTE)
  (void)mblen(NULL, 0);
#endif
  
  /*
   * Continue until end of string is reached, a whitespace is encountered,
   * or width is exceeded
   */
  for (i = 0;
       ((width == NO_WIDTH) || (i < width)) &&
       (! ((self->current == EOF) || isspace(self->current)));
       )
    {
      size = TrioReadWideChar(self, &target[i], flags, 1);
      if (size == 0)
	break; /* for */

      i += size;
    }
  if (target)
    target[i] = WCONST('\0');
  return TRUE;
}
