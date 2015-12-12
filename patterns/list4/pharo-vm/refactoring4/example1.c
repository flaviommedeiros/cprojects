# if !defined(USE_XSHM)
if (!useXshm && depth == stBitsPerPixel &&
	  (depth != 16 || stHasSameRGBMask16) &&
	  (depth != 32 || stHasSameRGBMask32))
#    else
      if (!useXshm && depth == stBitsPerPixel && depth == 32 && stHasSameRGBMask32)
#    endif
	{
	  stDisplayBitmap= 0;
	}
      else
	{
	  stDisplayBitmap= stMalloc(bytesPerLine(width, stBitsPerPixel) * height);
	}
