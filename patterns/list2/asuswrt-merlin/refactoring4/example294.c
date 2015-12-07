#if HAVE_NATIVE_64_BIT
if (length & SERPENT_BLOCK_SIZE)
#else
  while (length >= SERPENT_BLOCK_SIZE)
#endif
    {
      uint32_t x0,x1,x2,x3, y0,y1,y2,y3;
      unsigned k;

      x0 = LE_READ_UINT32 (src);
      x1 = LE_READ_UINT32 (src + 4);
      x2 = LE_READ_UINT32 (src + 8);
      x3 = LE_READ_UINT32 (src + 12);

      /* Inverse of special round */
      KEYXOR (x0,x1,x2,x3, ctx->keys[32]);
      SBOX7_INVERSE (x0,x1,x2,x3, y0,y1,y2,y3);
      KEYXOR (y0,y1,y2,y3, ctx->keys[31]);

      k = 24;
      goto start32;
      while (k > 0)
	{
	  k -= 8;
	  ROUND_INVERSE (7, ctx->keys[k+7], x0,x1,x2,x3, y0,y1,y2,y3);
	start32:
	  ROUND_INVERSE (6, ctx->keys[k+6], y0,y1,y2,y3, x0,x1,x2,x3);
	  ROUND_INVERSE (5, ctx->keys[k+5], x0,x1,x2,x3, y0,y1,y2,y3);
	  ROUND_INVERSE (4, ctx->keys[k+4], y0,y1,y2,y3, x0,x1,x2,x3);
	  ROUND_INVERSE (3, ctx->keys[k+3], x0,x1,x2,x3, y0,y1,y2,y3);
	  ROUND_INVERSE (2, ctx->keys[k+2], y0,y1,y2,y3, x0,x1,x2,x3);
	  ROUND_INVERSE (1, ctx->keys[k+1], x0,x1,x2,x3, y0,y1,y2,y3);
	  ROUND_INVERSE (0, ctx->keys[k], y0,y1,y2,y3, x0,x1,x2,x3);
	}
      
      LE_WRITE_UINT32 (dst, x0);
      LE_WRITE_UINT32 (dst + 4, x1);
      LE_WRITE_UINT32 (dst + 8, x2);
      LE_WRITE_UINT32 (dst + 12, x3);

      src += SERPENT_BLOCK_SIZE;
      dst += SERPENT_BLOCK_SIZE;
      length -= SERPENT_BLOCK_SIZE;
    }
