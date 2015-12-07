if ((QUALIFIER_STAR == format[index])
#if defined(QUALIFIER_PARAM)
			  || (QUALIFIER_PARAM == format[index])
#endif
			  )
			{
			  index++;
			  flags |= FLAGS_BASE_PARAMETER;
			  base = TrioGetPosition(format, &index);
			  if (base == NO_POSITION)
			    {
			      parameterPosition++;
			      if (positional)
				base = parameterPosition;
			      else
				{
				  base = currentParam;
				  currentParam = base + 1;
				}
			    }
			  else
			    {
			      if (! positional)
				currentParam = base + 1;
			      if (base > maxParam)
				maxParam = base;
			    }
			  if (currentParam > maxParam)
			    maxParam = currentParam;
			}
		      else
			{
			  base = trio_to_long(&format[index],
					      &tmpformat,
					      BASE_DECIMAL);
			  if (base > MAX_BASE)
			    return TRIO_ERROR_RETURN(TRIO_EINVAL, index);
			  index = (int)(tmpformat - format);
			}
