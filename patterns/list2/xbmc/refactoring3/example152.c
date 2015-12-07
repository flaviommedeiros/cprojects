switch (pBuf->iColortype)            /* determine magnification routines */
  {
#ifndef MNG_OPTIMIZE_FOOTPRINT_MAGN
    case  0 : ;
    case  8 : {
                if (pBuf->iBitdepth <= 8)
                {
                  switch (pImage->iMAGN_MethodX)
                  {
                    case 1  : { fMagnifyX = mng_magnify_g8_x1; break; }
                    case 2  : { fMagnifyX = mng_magnify_g8_x2; break; }
                    case 3  : { fMagnifyX = mng_magnify_g8_x3; break; }
                    case 4  : { fMagnifyX = mng_magnify_g8_x2; break; }
                    case 5  : { fMagnifyX = mng_magnify_g8_x3; break; }
                  }

                  switch (pImage->iMAGN_MethodY)
                  {
                    case 1  : { fMagnifyY = mng_magnify_g8_y1; break; }
                    case 2  : { fMagnifyY = mng_magnify_g8_y2; break; }
                    case 3  : { fMagnifyY = mng_magnify_g8_y3; break; }
                    case 4  : { fMagnifyY = mng_magnify_g8_y2; break; }
                    case 5  : { fMagnifyY = mng_magnify_g8_y3; break; }
                  }
                }
#ifndef MNG_NO_16BIT_SUPPORT
                else
                {
                  switch (pImage->iMAGN_MethodX)
                  {
                    case 1  : { fMagnifyX = mng_magnify_g16_x1; break; }
                    case 2  : { fMagnifyX = mng_magnify_g16_x2; break; }
                    case 3  : { fMagnifyX = mng_magnify_g16_x3; break; }
                    case 4  : { fMagnifyX = mng_magnify_g16_x2; break; }
                    case 5  : { fMagnifyX = mng_magnify_g16_x3; break; }
                  }

                  switch (pImage->iMAGN_MethodY)
                  {
                    case 1  : { fMagnifyY = mng_magnify_g16_y1; break; }
                    case 2  : { fMagnifyY = mng_magnify_g16_y2; break; }
                    case 3  : { fMagnifyY = mng_magnify_g16_y3; break; }
                    case 4  : { fMagnifyY = mng_magnify_g16_y2; break; }
                    case 5  : { fMagnifyY = mng_magnify_g16_y3; break; }
                  }
                }
#endif

                break;
              }

    case  2 : ;
    case 10 : {
                if (pBuf->iBitdepth <= 8)
                {
                  switch (pImage->iMAGN_MethodX)
                  {
                    case 1  : { fMagnifyX = mng_magnify_rgb8_x1; break; }
                    case 2  : { fMagnifyX = mng_magnify_rgb8_x2; break; }
                    case 3  : { fMagnifyX = mng_magnify_rgb8_x3; break; }
                    case 4  : { fMagnifyX = mng_magnify_rgb8_x2; break; }
                    case 5  : { fMagnifyX = mng_magnify_rgb8_x3; break; }
                  }

                  switch (pImage->iMAGN_MethodY)
                  {
                    case 1  : { fMagnifyY = mng_magnify_rgb8_y1; break; }
                    case 2  : { fMagnifyY = mng_magnify_rgb8_y2; break; }
                    case 3  : { fMagnifyY = mng_magnify_rgb8_y3; break; }
                    case 4  : { fMagnifyY = mng_magnify_rgb8_y2; break; }
                    case 5  : { fMagnifyY = mng_magnify_rgb8_y3; break; }
                  }
                }
#ifndef MNG_NO_16BIT_SUPPORT
                else
                {
                  switch (pImage->iMAGN_MethodX)
                  {
                    case 1  : { fMagnifyX = mng_magnify_rgb16_x1; break; }
                    case 2  : { fMagnifyX = mng_magnify_rgb16_x2; break; }
                    case 3  : { fMagnifyX = mng_magnify_rgb16_x3; break; }
                    case 4  : { fMagnifyX = mng_magnify_rgb16_x2; break; }
                    case 5  : { fMagnifyX = mng_magnify_rgb16_x3; break; }
                  }

                  switch (pImage->iMAGN_MethodY)
                  {
                    case 1  : { fMagnifyY = mng_magnify_rgb16_y1; break; }
                    case 2  : { fMagnifyY = mng_magnify_rgb16_y2; break; }
                    case 3  : { fMagnifyY = mng_magnify_rgb16_y3; break; }
                    case 4  : { fMagnifyY = mng_magnify_rgb16_y2; break; }
                    case 5  : { fMagnifyY = mng_magnify_rgb16_y3; break; }
                  }
                }
#endif

                break;
              }

    case  4 : ;
    case 12 : {
                if (pBuf->iBitdepth <= 8)
                {
                  switch (pImage->iMAGN_MethodX)
                  {
                    case 1  : { fMagnifyX = mng_magnify_ga8_x1; break; }
                    case 2  : { fMagnifyX = mng_magnify_ga8_x2; break; }
                    case 3  : { fMagnifyX = mng_magnify_ga8_x3; break; }
                    case 4  : { fMagnifyX = mng_magnify_ga8_x4; break; }
                    case 5  : { fMagnifyX = mng_magnify_ga8_x5; break; }
                  }

                  switch (pImage->iMAGN_MethodY)
                  {
                    case 1  : { fMagnifyY = mng_magnify_ga8_y1; break; }
                    case 2  : { fMagnifyY = mng_magnify_ga8_y2; break; }
                    case 3  : { fMagnifyY = mng_magnify_ga8_y3; break; }
                    case 4  : { fMagnifyY = mng_magnify_ga8_y4; break; }
                    case 5  : { fMagnifyY = mng_magnify_ga8_y5; break; }
                  }
                }
#ifndef MNG_NO_16BIT_SUPPORT
                else
                {
                  switch (pImage->iMAGN_MethodX)
                  {
                    case 1  : { fMagnifyX = mng_magnify_ga16_x1; break; }
                    case 2  : { fMagnifyX = mng_magnify_ga16_x2; break; }
                    case 3  : { fMagnifyX = mng_magnify_ga16_x3; break; }
                    case 4  : { fMagnifyX = mng_magnify_ga16_x4; break; }
                    case 5  : { fMagnifyX = mng_magnify_ga16_x5; break; }
                  }

                  switch (pImage->iMAGN_MethodY)
                  {
                    case 1  : { fMagnifyY = mng_magnify_ga16_y1; break; }
                    case 2  : { fMagnifyY = mng_magnify_ga16_y2; break; }
                    case 3  : { fMagnifyY = mng_magnify_ga16_y3; break; }
                    case 4  : { fMagnifyY = mng_magnify_ga16_y4; break; }
                    case 5  : { fMagnifyY = mng_magnify_ga16_y5; break; }
                  }
                }
#endif

                break;
              }
#endif

    case  6 : ;
    case 14 : {
                if (pBuf->iBitdepth <= 8)
                {
                  switch (pImage->iMAGN_MethodX)
                  {
                    case 1  : { fMagnifyX = mng_magnify_rgba8_x1; break; }
                    case 2  : { fMagnifyX = mng_magnify_rgba8_x2; break; }
                    case 3  : { fMagnifyX = mng_magnify_rgba8_x3; break; }
                    case 4  : { fMagnifyX = mng_magnify_rgba8_x4; break; }
                    case 5  : { fMagnifyX = mng_magnify_rgba8_x5; break; }
                  }

                  switch (pImage->iMAGN_MethodY)
                  {
                    case 1  : { fMagnifyY = mng_magnify_rgba8_y1; break; }
                    case 2  : { fMagnifyY = mng_magnify_rgba8_y2; break; }
                    case 3  : { fMagnifyY = mng_magnify_rgba8_y3; break; }
                    case 4  : { fMagnifyY = mng_magnify_rgba8_y4; break; }
                    case 5  : { fMagnifyY = mng_magnify_rgba8_y5; break; }
                  }
                }
#ifndef MNG_NO_16BIT_SUPPORT
#ifndef MNG_OPTIMIZE_FOOTPRINT_MAGN
                else
                {
                  switch (pImage->iMAGN_MethodX)
                  {
                    case 1  : { fMagnifyX = mng_magnify_rgba16_x1; break; }
                    case 2  : { fMagnifyX = mng_magnify_rgba16_x2; break; }
                    case 3  : { fMagnifyX = mng_magnify_rgba16_x3; break; }
                    case 4  : { fMagnifyX = mng_magnify_rgba16_x4; break; }
                    case 5  : { fMagnifyX = mng_magnify_rgba16_x5; break; }
                  }

                  switch (pImage->iMAGN_MethodY)
                  {
                    case 1  : { fMagnifyY = mng_magnify_rgba16_y1; break; }
                    case 2  : { fMagnifyY = mng_magnify_rgba16_y2; break; }
                    case 3  : { fMagnifyY = mng_magnify_rgba16_y3; break; }
                    case 4  : { fMagnifyY = mng_magnify_rgba16_y4; break; }
                    case 5  : { fMagnifyY = mng_magnify_rgba16_y5; break; }
                  }
                }
#endif
#endif
                break;
              }
  }
