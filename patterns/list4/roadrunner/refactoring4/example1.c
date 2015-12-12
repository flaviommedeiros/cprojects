#if LDOUBLE_SIZE != 8
if(r2 == VT_LDOUBLE)
	func=TOK___fixunsxfsi;
      else if(r2 == VT_DOUBLE)
#else
      else if(r2 == VT_LDOUBLE || r2 == VT_DOUBLE)
#endif
	func=TOK___fixunsdfsi;
