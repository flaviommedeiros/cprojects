#ifdef USE_AESNI
if (ctx->use_aesni)
    {
      /* The AES-NI decrypt instructions use the Equivalent Inverse
         Cipher, thus we can't use the the standard decrypt key
         preparation.  */
        m128i_t *ekey = (m128i_t*)ctx->keyschenc;
        m128i_t *dkey = (m128i_t*)ctx->keyschdec;
        int rr;

        dkey[0] = ekey[ctx->rounds];
        for (r=1, rr=ctx->rounds-1; r < ctx->rounds; r++, rr--)
          {
            asm volatile
              ("movdqu %[ekey], %%xmm1\n\t"
               /*"aesimc %%xmm1, %%xmm1\n\t"*/
               ".byte 0x66, 0x0f, 0x38, 0xdb, 0xc9\n\t"
               "movdqu %%xmm1, %[dkey]"
               : [dkey] "=m" (dkey[r])
               : [ekey] "m" (ekey[rr]) );
          }
        dkey[r] = ekey[0];
    }
  else
#endif /*USE_AESNI*/
    {
      union
      {
        PROPERLY_ALIGNED_TYPE dummy;
        byte *w;
      } w;
#define w w.w

      for (r=0; r < MAXROUNDS+1; r++ )
        {
          *((u32*)ctx->keyschdec[r][0]) = *((u32*)ctx->keyschenc[r][0]);
          *((u32*)ctx->keyschdec[r][1]) = *((u32*)ctx->keyschenc[r][1]);
          *((u32*)ctx->keyschdec[r][2]) = *((u32*)ctx->keyschenc[r][2]);
          *((u32*)ctx->keyschdec[r][3]) = *((u32*)ctx->keyschenc[r][3]);
        }
#define W (ctx->keyschdec)
      for (r = 1; r < ctx->rounds; r++)
        {
          w = W[r][0];
          *((u32*)w) = *((u32*)U1[w[0]]) ^ *((u32*)U2[w[1]])
            ^ *((u32*)U3[w[2]]) ^ *((u32*)U4[w[3]]);

          w = W[r][1];
          *((u32*)w) = *((u32*)U1[w[0]]) ^ *((u32*)U2[w[1]])
            ^ *((u32*)U3[w[2]]) ^ *((u32*)U4[w[3]]);

          w = W[r][2];
          *((u32*)w) = *((u32*)U1[w[0]]) ^ *((u32*)U2[w[1]])
        ^ *((u32*)U3[w[2]]) ^ *((u32*)U4[w[3]]);

          w = W[r][3];
          *((u32*)w) = *((u32*)U1[w[0]]) ^ *((u32*)U2[w[1]])
            ^ *((u32*)U3[w[2]]) ^ *((u32*)U4[w[3]]);
        }
#undef W
#undef w
    }
