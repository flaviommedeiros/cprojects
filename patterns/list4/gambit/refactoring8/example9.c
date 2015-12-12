___SCMOBJ ___addr_to_SCMOBJ
   ___P((void *sa,
         int salen,
         int arg_num),
        (sa,
         salen,
         arg_num)
void *sa;
int salen;
int arg_num;)
{
  ___SCMOBJ result;

  if (salen == 4)
    {
      struct in_addr *ia = ___CAST(struct in_addr*,sa);
      ___U32 a;

      result = ___alloc_scmobj (___PSTATE, ___sU8VECTOR, 4);

      if (___FIXNUMP(result))
        return ___FIX(___CTOS_HEAP_OVERFLOW_ERR+arg_num);

      a = ntohl (ia->s_addr);

      ___U8VECTORSET(result,___FIX(0),___FIX((a>>24)&0xff))
      ___U8VECTORSET(result,___FIX(1),___FIX((a>>16)&0xff))
      ___U8VECTORSET(result,___FIX(2),___FIX((a>>8)&0xff))
      ___U8VECTORSET(result,___FIX(3),___FIX(a&0xff))
    }
#ifdef USE_IPV6
  else if (salen == 16)
    {
      struct in6_addr *ia = ___CAST(struct in6_addr*,sa);
      int i;

      result = ___alloc_scmobj (___PSTATE, ___sU16VECTOR, 8<<1);

      if (___FIXNUMP(result))
        return ___FIX(___CTOS_HEAP_OVERFLOW_ERR+arg_num);

      for (i=0; i<8; i++)
        ___U16VECTORSET(result,
                        ___FIX(i),
                        ___FIX((___CAST(___U16,ia->s6_addr[i<<1])<<8)
                               +ia->s6_addr[(i<<1)+1]))
    }
#endif
  else
    result = ___FAL;

  return result;
}
