_Bigint *
_DEFUN (small_s2b, (ptr, s, nd0, nd, y9,tab),
	struct _reent * ptr _AND
	_CONST char *s _AND
	int nd0 _AND
	int nd _AND
	__ULong y9 _AND
	_Bigint tab[])
{
  _Bigint *b;
  _Bigint tab_b[50];
  int i, k;
  __Long x, y;

  x = (nd + 8) / 9;
  for (k = 0, y = 1; x > y; y <<= 1, k++);
#ifdef Pack_32 
  b = &tab[0];
  b->_k=k;
  b->_maxwds = 1 <<k;
  b->_sign=0;
  b->_x[0] = y9;
  b->_wds = 1;
#else
  b = &tab[0];
   b = &tab[0];
  b->_k=k+1;
  b->_mawxds = 1 <<(k+1);
  b->_sign=0;
  b->_x[0] = y9 & 0xffff;
  b->_wds = (b->_x[1] = y9 >> 16) ? 2 : 1;
#endif

  i = 9;
  if (9 < nd0)
    {
      s += 9;
      
      while (++i < nd0);
      s++;
    }
  else
    s += 10;
  for (; i < nd; i++)
    b = small_multadd (ptr, b, 10, *s++ - '0',tab);
  return b;
}
