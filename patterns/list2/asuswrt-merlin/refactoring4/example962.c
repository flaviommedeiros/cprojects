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

      for (k = 0; ; k += 8)
	{
	  ROUND (0, ctx->keys[k+0], x0,x1,x2,x3, y0,y1,y2,y3);
	  ROUND (1, ctx->keys[k+1], y0,y1,y2,y3, x0,x1,x2,x3);
	  ROUND (2, ctx->keys[k+2], x0,x1,x2,x3, y0,y1,y2,y3);
	  ROUND (3, ctx->keys[k+3], y0,y1,y2,y3, x0,x1,x2,x3);
	  ROUND (4, ctx->keys[k+4], x0,x1,x2,x3, y0,y1,y2,y3);
	  ROUND (5, ctx->keys[k+5], y0,y1,y2,y3, x0,x1,x2,x3);
	  ROUND (6, ctx->keys[k+6], x0,x1,x2,x3, y0,y1,y2,y3);
	  if (k == 24)
	    break;
	  ROUND (7, ctx->keys[k+7], y0,y1,y2,y3, x0,x1,x2,x3);
	}

      /* Special final round, using two subkeys. */
      KEYXOR (y0,y1,y2,y3, ctx->keys[31]);
      SBOX7 (y0,y1,y2,y3, x0,x1,x2,x3);
      KEYXOR (x0,x1,x2,x3, ctx->keys[32]);
    
      LE_WRITE_UINT32 (dst, x0);
      LE_WRITE_UINT32 (dst + 4, x1);
      LE_WRITE_UINT32 (dst + 8, x2);
      LE_WRITE_UINT32 (dst + 12, x3);

      src += SERPENT_BLOCK_SIZE;
      dst += SERPENT_BLOCK_SIZE;
      length -= SERPENT_BLOCK_SIZE;
    }
