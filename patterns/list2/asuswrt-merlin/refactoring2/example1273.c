#ifdef ALIGNMENT_32BIT_REQUIRED
if ((((uint32_t) &s[0]) & 0x3) != 0)
#endif
  {
	  x->v8[0]  = s[0];
	  x->v8[1]  = s[1];
	  x->v8[2]  = s[2];
	  x->v8[3]  = s[3];
	  x->v8[4]  = s[4];
	  x->v8[5]  = s[5];
	  x->v8[6]  = s[6];
	  x->v8[7]  = s[7];
	  x->v8[8]  = s[8];
	  x->v8[9]  = s[9];
	  x->v8[10] = s[10];
	  x->v8[11] = s[11];
	  x->v8[12] = s[12];
	  x->v8[13] = s[13];
	  x->v8[14] = s[14];
	  x->v8[15] = s[15];
  }
#ifdef ALIGNMENT_32BIT_REQUIRED
  else 
  {
	  v128_t *v = (v128_t *) &s[0];

	  v128_copy(x,v);
  }
