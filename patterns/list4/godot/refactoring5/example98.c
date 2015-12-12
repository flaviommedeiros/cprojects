#ifdef STRICT_ALIGNMENT
if ((size_t)p & 7)
		{
		memcpy (S.c,p,64);
		S.q[0] ^= (K.q[0] = H->q[0]);
		S.q[1] ^= (K.q[1] = H->q[1]);
		S.q[2] ^= (K.q[2] = H->q[2]);
		S.q[3] ^= (K.q[3] = H->q[3]);
		S.q[4] ^= (K.q[4] = H->q[4]);
		S.q[5] ^= (K.q[5] = H->q[5]);
		S.q[6] ^= (K.q[6] = H->q[6]);
		S.q[7] ^= (K.q[7] = H->q[7]);
		}
	else
#endif
		{
		const u64 *pa = (const u64*)p;
		S.q[0] = (K.q[0] = H->q[0]) ^ pa[0];
		S.q[1] = (K.q[1] = H->q[1]) ^ pa[1];
		S.q[2] = (K.q[2] = H->q[2]) ^ pa[2];
		S.q[3] = (K.q[3] = H->q[3]) ^ pa[3];
		S.q[4] = (K.q[4] = H->q[4]) ^ pa[4];
		S.q[5] = (K.q[5] = H->q[5]) ^ pa[5];
		S.q[6] = (K.q[6] = H->q[6]) ^ pa[6];
		S.q[7] = (K.q[7] = H->q[7]) ^ pa[7];
		}
