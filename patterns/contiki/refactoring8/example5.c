_Bigint *
_DEFUN (s2b, (ptr, s, nd0, nd, y9),
	struct _reent * ptr _AND
	_CONST char *s _AND
	int nd0 _AND
	int nd _AND
	__ULong y9)
{
  _Bigint *b;
  int i, k;
  __Long x, y;

  x = (nd + 8) / 9;
  for (k = 0, y = 1; x > y; y <<= 1, k++);
#ifdef Pack_32
  b = Balloc (ptr, k);
  b->_x[0] = y9;
  b->_wds = 1;
#else
  b = Balloc (ptr, k + 1);
  b->_x[0] = y9 & 0xffff;
  b->_wds = (b->_x[1] = y9 >> 16) ? 2 : 1;
#endif

  i = 9;
  if (9 < nd0)
    {
      s += 9;
      do
	b = multadd (ptr, b, 10, *s++ - '0');
      while (++i < nd0);
      s++;
    }
  else
    s += 10;
  for (; i < nd; i++)
    b = multadd (ptr, b, 10, *s++ - '0');
  return b;
}
