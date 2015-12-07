switch(im->bits_per_pixel)
	{
#if 1
	  case 8:
	    for(y = 0; y < height; y++)
		for(x = 0; x < width; x++)
		{
		    c = pseudoImage[(sy + y) * REAL_SCREEN_SIZE_X + sx + x];
		    im->data[(sy + y) * units_per_line + sx + x] = pixels[c];
		}
	    break;
	  case 16:
	    for(y = 0; y < height; y++)
		for(x = 0; x < width; x++)
		{
		    c = pseudoImage[(sy + y) * REAL_SCREEN_SIZE_X + sx + x];
		    ((uint16 *)im->data)[(sy + y) * units_per_line + sx + x]
			= pixels[c];
		}
	    break;
	  case 32:
	    for(y = 0; y < height; y++)
		for(x = 0; x < width; x++)
		{
		    c = pseudoImage[(sy + y) * REAL_SCREEN_SIZE_X + sx + x];
		    ((uint32 *)im->data)[(sy + y) * units_per_line + sx + x]
			= pixels[c];
		}
	    break;
#endif
	  default: /* Generic routine */
	    for(y = 0; y < height; y++)
		for(x = 0; x < width; x++)
		{
		    c = pseudoImage[(sy + y) * REAL_SCREEN_SIZE_X + sx + x];
		    XPutPixel(theRealScreen->im, sx + x, sy + y, pixels[c]);
		}
	    break;
	}
