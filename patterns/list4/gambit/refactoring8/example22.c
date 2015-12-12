___HIDDEN ___SCMOBJ *align
   ___P((___SCMOBJ *from,
         ___SIZE_TS words,
         int need_64bit_alignment),
        (from,
         words,
         need_64bit_alignment)
___SCMOBJ *from;
___SIZE_TS words;
int need_64bit_alignment;)
{
  ___SCMOBJ *to;

#if ___WS == 4
  if (need_64bit_alignment)
    to = ___ALIGNUP((from+1), 8) - 1;
  else
#endif
    to = ___ALIGNUP(from, ___WS);

  if (from != to)
    {
      /* move object up */
      int i;
      for (i=words-1; i>=0; i--)
        to[i] = from[i];
    }

  return to;
}
