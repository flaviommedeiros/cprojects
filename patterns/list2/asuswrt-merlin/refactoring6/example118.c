if ((QUALIFIER_STAR == format[index])
#if defined(QUALIFIER_PARAM)
			  || (QUALIFIER_PARAM == format[index])
#endif
			  )
			{
			  index++;
			  flags |= FLAGS_PRECISION_PARAMETER;

			  precision = TrioGetPosition(format, &index);
			  if (precision == NO_POSITION)
			    {
			      parameterPosition++;
			      if (positional)
				precision = parameterPosition;
			      else
				{
				  precision = currentParam;
				  currentParam = precision + 1;
				}
			    }
			  else
			    {
			      if (! positional)
				currentParam = precision + 1;
			      if (width > maxParam)
				maxParam = precision;
			    }
			  if (currentParam > maxParam)
			    maxParam = currentParam;
			}
		      else
			{
			  precision = trio_to_long(&format[index],
						   &tmpformat,
						   BASE_DECIMAL);
			  index = (int)(tmpformat - format);
			}
