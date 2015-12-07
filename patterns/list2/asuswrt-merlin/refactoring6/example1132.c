if ((*source == 'e')
	  || (*source == 'E')
#if TRIO_MICROSOFT
	  || (*source == 'd')
	  || (*source == 'D')
#endif
	  )
	{
	  source++; /* Skip exponential indicator */
	  isExponentNegative = (*source == '-');
	  if ((*source == '+') || (*source == '-'))
	    source++;
	  while (isdigit((int)*source))
	    {
	      exponent *= (int)base;
	      exponent += (*source - '0');
	      source++;
	    }
	}
