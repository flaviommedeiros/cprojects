TRIO_PRIVATE int
TrioGetPosition
TRIO_ARGS2((format, indexPointer),
	   TRIO_CONST char *format,
	   int *indexPointer)
{
#if TRIO_UNIX98
  char *tmpformat;
  int number = 0;
  int index = *indexPointer;

  number = (int)trio_to_long(&format[index], &tmpformat, BASE_DECIMAL);
  index = (int)(tmpformat - format);
  if ((number != 0) && (QUALIFIER_POSITION == format[index++]))
    {
      *indexPointer = index;
      /*
       * number is decreased by 1, because n$ starts from 1, whereas
       * the array it is indexing starts from 0.
       */
      return number - 1;
    }
#endif
  return NO_POSITION;
}
