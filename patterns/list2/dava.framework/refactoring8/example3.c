TRIO_PRIVATE int
TrioGetCharacterClass
TRIO_ARGS4((format, indexPointer, flagsPointer, characterclass),
	   TRIO_CONST char *format,
	   int *indexPointer,
	   trio_flags_t *flagsPointer,
	   int *characterclass)
{
  int index = *indexPointer;
  int i;
  char ch;
  char range_begin;
  char range_end;

  *flagsPointer &= ~FLAGS_EXCLUDE;

  if (format[index] == QUALIFIER_CIRCUMFLEX)
    {
      *flagsPointer |= FLAGS_EXCLUDE;
      index++;
    }
  /*
   * If the ungroup character is at the beginning of the scanlist,
   * it will be part of the class, and a second ungroup character
   * must follow to end the group.
   */
  if (format[index] == SPECIFIER_UNGROUP)
    {
      characterclass[(int)SPECIFIER_UNGROUP]++;
      index++;
    }
  /*
   * Minus is used to specify ranges. To include minus in the class,
   * it must be at the beginning of the list
   */
  if (format[index] == QUALIFIER_MINUS)
    {
      characterclass[(int)QUALIFIER_MINUS]++;
      index++;
    }
  /* Collect characters */
  for (ch = format[index];
       (ch != SPECIFIER_UNGROUP) && (ch != NIL);
       ch = format[++index])
    {
      switch (ch)
	{
	case QUALIFIER_MINUS: /* Scanlist ranges */
	  
	  /*
	   * Both C99 and UNIX98 describes ranges as implementation-
	   * defined.
	   *
	   * We support the following behaviour (although this may
	   * change as we become wiser)
	   * - only increasing ranges, ie. [a-b] but not [b-a]
	   * - transitive ranges, ie. [a-b-c] == [a-c]
	   * - trailing minus, ie. [a-] is interpreted as an 'a'
	   *   and a '-'
	   * - duplicates (although we can easily convert these
	   *   into errors)
	   */
	  range_begin = format[index - 1];
	  range_end = format[++index];
	  if (range_end == SPECIFIER_UNGROUP)
	    {
	      /* Trailing minus is included */
	      characterclass[(int)ch]++;
	      ch = range_end;
	      break; /* for */
	    }
	  if (range_end == NIL)
	    return TRIO_ERROR_RETURN(TRIO_EINVAL, index);
	  if (range_begin > range_end)
	    return TRIO_ERROR_RETURN(TRIO_ERANGE, index);
	    
	  for (i = (int)range_begin; i <= (int)range_end; i++)
	    characterclass[i]++;
	    
	  ch = range_end;
	  break;
	  
#if TRIO_EXTENSION

	case SPECIFIER_GROUP:
	  
	  switch (format[index + 1])
	    {
	    case QUALIFIER_DOT: /* Collating symbol */
	      /*
	       * FIXME: This will be easier to implement when multibyte
	       * characters have been implemented. Until now, we ignore
	       * this feature.
	       */
	      for (i = index + 2; ; i++)
		{
		  if (format[i] == NIL)
		    /* Error in syntax */
		    return -1;
		  else if (format[i] == QUALIFIER_DOT)
		    break; /* for */
		}
	      if (format[++i] != SPECIFIER_UNGROUP)
		return -1;
	      
	      index = i;
	      break;
	  
	    case QUALIFIER_EQUAL: /* Equivalence class expressions */
	      {
		unsigned int j;
		unsigned int k;
	    
		if (internalCollationUnconverted)
		  {
		    /* Lazy evaluation of collation array */
		    TrioGetCollation();
		    internalCollationUnconverted = FALSE;
		  }
		for (i = index + 2; ; i++)
		  {
		    if (format[i] == NIL)
		      /* Error in syntax */
		      return -1;
		    else if (format[i] == QUALIFIER_EQUAL)
		      break; /* for */
		    else
		      {
			/* Mark any equivalent character */
			k = (unsigned int)format[i];
			for (j = 0; internalCollationArray[k][j] != NIL; j++)
			  characterclass[(int)internalCollationArray[k][j]]++;
		      }
		  }
		if (format[++i] != SPECIFIER_UNGROUP)
		  return -1;
		
		index = i;
	      }
	      break;
	  
	    case QUALIFIER_COLON: /* Character class expressions */
	  
	      if (trio_equal_max(CLASS_ALNUM, sizeof(CLASS_ALNUM) - 1,
				 &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (isalnum(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_ALNUM) - 1;
		}
	      else if (trio_equal_max(CLASS_ALPHA, sizeof(CLASS_ALPHA) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (isalpha(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_ALPHA) - 1;
		}
	      else if (trio_equal_max(CLASS_CNTRL, sizeof(CLASS_CNTRL) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (iscntrl(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_CNTRL) - 1;
		}
	      else if (trio_equal_max(CLASS_DIGIT, sizeof(CLASS_DIGIT) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (isdigit(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_DIGIT) - 1;
		}
	      else if (trio_equal_max(CLASS_GRAPH, sizeof(CLASS_GRAPH) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (isgraph(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_GRAPH) - 1;
		}
	      else if (trio_equal_max(CLASS_LOWER, sizeof(CLASS_LOWER) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (islower(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_LOWER) - 1;
		}
	      else if (trio_equal_max(CLASS_PRINT, sizeof(CLASS_PRINT) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (isprint(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_PRINT) - 1;
		}
	      else if (trio_equal_max(CLASS_PUNCT, sizeof(CLASS_PUNCT) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (ispunct(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_PUNCT) - 1;
		}
	      else if (trio_equal_max(CLASS_SPACE, sizeof(CLASS_SPACE) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (isspace(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_SPACE) - 1;
		}
	      else if (trio_equal_max(CLASS_UPPER, sizeof(CLASS_UPPER) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (isupper(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_UPPER) - 1;
		}
	      else if (trio_equal_max(CLASS_XDIGIT, sizeof(CLASS_XDIGIT) - 1,
				      &format[index]))
		{
		  for (i = 0; i < MAX_CHARACTER_CLASS; i++)
		    if (isxdigit(i))
		      characterclass[i]++;
		  index += sizeof(CLASS_XDIGIT) - 1;
		}
	      else
		{
		  characterclass[(int)ch]++;
		}
	      break;

	    default:
	      characterclass[(int)ch]++;
	      break;
	    }
	  break;
	  
#endif /* TRIO_EXTENSION */
	  
	default:
	  characterclass[(int)ch]++;
	  break;
	}
    }
  return 0;
}
