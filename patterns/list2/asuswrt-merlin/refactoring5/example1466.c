# ifdef STRICT_ALIGNMENT
if ((size_t)p & 7) {
            int i;
            for (i = 0; i < 64; i++)
                H->c[i] ^= S.c[i] ^ p[i];
        } else
# endif
        {
            const u64 *pa = (const u64 *)p;
            H->q[0] ^= S.q[0] ^ pa[0];
            H->q[1] ^= S.q[1] ^ pa[1];
            H->q[2] ^= S.q[2] ^ pa[2];
            H->q[3] ^= S.q[3] ^ pa[3];
            H->q[4] ^= S.q[4] ^ pa[4];
            H->q[5] ^= S.q[5] ^ pa[5];
            H->q[6] ^= S.q[6] ^ pa[6];
            H->q[7] ^= S.q[7] ^ pa[7];
        }
