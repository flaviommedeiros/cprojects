TRIO_PRIVATE int
TrioFormat
TRIO_ARGS6((destination, destinationSize, OutStream, format, arglist, argarray),
	   trio_pointer_t destination,
	   size_t destinationSize,
	   void (*OutStream) TRIO_PROTO((trio_class_t *, int)),
	   TRIO_CONST char *format,
	   va_list *arglist,
	   trio_pointer_t *argarray)
{
  int status;
  trio_class_t data;
  trio_parameter_t parameters[MAX_PARAMETERS];

  assert(VALID(OutStream));
  assert(VALID(format));

  memset(&data, 0, sizeof(data));
  data.OutStream = OutStream;
  data.location = destination;
  data.max = destinationSize;
  data.error = 0;

#if defined(USE_LOCALE)
  if (NULL == internalLocaleValues)
    {
      TrioSetLocale();
    }
#endif

  status = TrioParse(TYPE_PRINT, format, parameters, arglist, argarray);
  if (status < 0)
    return status;

  status = TrioFormatProcess(&data, format, parameters);
  if (data.error != 0)
    {
      status = data.error;
    }
  return status;
}
