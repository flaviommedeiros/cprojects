#ifdef _WIN32
if (sscanf(buff.data + buff.offset,
            "%I64d",
            (signed long long*)&value->val.int_) == 0)
#else
   if (sscanf(buff.data + buff.offset,
            "%lld",
            (signed long long*)&value->val.int_) == 0)
#endif
      raise_expected_number(buff.offset, error);
   else
   {
      while (isdigit((int)buff.data[buff.offset]))
         buff.offset++;
   }
