TRIO_PRIVATE int
TrioScan
TRIO_ARGS6((source, sourceSize, InStream, format, arglist, argarray),
	   trio_pointer_t source,
	   size_t sourceSize,
	   void (*InStream) TRIO_PROTO((trio_class_t *, int *)),
	   TRIO_CONST char *format,
	   va_list *arglist,
	   trio_pointer_t *argarray)
{
  int status;
  trio_parameter_t parameters[MAX_PARAMETERS];
  trio_class_t data;

  assert(VALID(InStream));
  assert(VALID(format));

  memset(&data, 0, sizeof(data));
  data.InStream = InStream;
  data.location = (trio_pointer_t)source;
  data.max = sourceSize;
  data.error = 0;

#if defined(USE_LOCALE)
  if (NULL == internalLocaleValues)
    {
      TrioSetLocale();
    }
#endif
  
  status = TrioParse(TYPE_SCAN, format, parameters, arglist, argarray);
  if (status < 0)
    return status;

  status = TrioScanProcess(&data, format, parameters);
  if (data.error != 0)
    {
      status = data.error;
    }
  return status;
}
