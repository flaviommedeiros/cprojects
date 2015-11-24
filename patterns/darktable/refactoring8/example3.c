static void xtrans_markesteijn_interpolate(float *out, const float *const in,
                                           const dt_iop_roi_t *const roi_out,
                                           const dt_iop_roi_t *const roi_in, const dt_image_t *img,
                                           const uint8_t (*const xtrans)[6], const int passes)
{
  static const short orth[12] = { 1, 0, 0, 1, -1, 0, 0, -1, 1, 0, 0, 1 },
                     patt[2][16] = { { 0, 1, 0, -1, 2, 0, -1, 0, 1, 1, 1, -1, 0, 0, 0, 0 },
                                     { 0, 1, 0, -2, 1, 0, -2, 0, 1, 1, -2, -2, 1, -1, -1, 1 } },
                     dir[4] = { 1, TS, TS + 1, TS - 1 };

  short allhex[3][3][8];
  // sgrow/sgcol is the offset in the sensor matrix of the solitary
  // green pixels (initialized here only to avoid compiler warning)
  unsigned short sgrow = 0, sgcol = 0;

  const int width = roi_out->width;
  const int height = roi_out->height;
  const int xoff = roi_in->x;
  const int yoff = roi_in->y;
  const int ndir = 4 << (passes > 1);

  const size_t buffer_size = (size_t)TS * TS * (ndir * 4 + 3) * sizeof(float);
  char *const all_buffers = (char *)dt_alloc_align(16, dt_get_num_threads() * buffer_size);
  if(!all_buffers)
  {
    printf("[demosaic] not able to allocate Markesteijn buffers\n");
    return;
  }

  /* Map a green hexagon around each non-green pixel and vice versa:    */
  for(int row = 0; row < 3; row++)
    for(int col = 0; col < 3; col++)
      for(int ng = 0, d = 0; d < 10; d += 2)
      {
        int g = FCxtrans(row, col, xtrans) == 1;
        if(FCxtrans(row + orth[d] + 6, col + orth[d + 2] + 6, xtrans) == 1)
          ng = 0;
        else
          ng++;
        // if there are four non-green pixels adjacent in cardinal
        // directions, this is the solitary green pixel
        if(ng == 4)
        {
          sgrow = row;
          sgcol = col;
        }
        if(ng == g + 1)
          for(int c = 0; c < 8; c++)
          {
            int v = orth[d] * patt[g][c * 2] + orth[d + 1] * patt[g][c * 2 + 1];
            int h = orth[d + 2] * patt[g][c * 2] + orth[d + 3] * patt[g][c * 2 + 1];
            // offset within TSxTS buffer
            allhex[row][col][c ^ (g * 2 & d)] = h + v * TS;
          }
      }

#ifdef _OPENMP
#pragma omp parallel for default(none) shared(sgrow, sgcol, allhex, out) schedule(dynamic)
#endif
  // step through TSxTS cells of image, each tile overlapping the
  // prior as interpolation needs a substantial border
  for(int top = -11; top < height - 11; top += TS - 22)
  {
    char *const buffer = all_buffers + dt_get_thread_num() * buffer_size;
    // rgb points to ndir TSxTS tiles of 3 channels (R, G, and B)
    float(*rgb)[TS][TS][3] = (float(*)[TS][TS][3])buffer;
    // yuv points to 3 channel (Y, u, and v) TSxTS tiles
    // note that channels come before tiles to allow for a
    // vectorization optimization when building drv[] from yuv[]
    float (*const yuv)[TS][TS] = (float(*)[TS][TS])(buffer + TS * TS * (ndir * 3) * sizeof(float));
    // drv points to ndir TSxTS tiles, each a single chanel of derivatives
    float (*const drv)[TS][TS] = (float(*)[TS][TS])(buffer + TS * TS * (ndir * 3 + 3) * sizeof(float));
    // gmin and gmax reuse memory which is used later by yuv buffer;
    // each points to a TSxTS tile of single channel data
    float (*const gmin)[TS] = (float(*)[TS])(buffer + TS * TS * (ndir * 3) * sizeof(float));
    float (*const gmax)[TS] = (float(*)[TS])(buffer + TS * TS * (ndir * 3 + 1) * sizeof(float));
    // homo and homosum reuse memory which is used earlier in the
    // loop; each points to ndir single-channel TSxTS tiles
    uint8_t (*const homo)[TS][TS] = (uint8_t(*)[TS][TS])(buffer + TS * TS * (ndir * 3) * sizeof(float));
    uint8_t (*const homosum)[TS][TS] = (uint8_t(*)[TS][TS])(buffer + TS * TS * (ndir * 3) * sizeof(float)
                                                            + TS * TS * ndir * sizeof(uint8_t));

    for(int left = -11; left < width - 11; left += TS - 22)
    {
      int mrow = MIN(top + TS, height + 11);
      int mcol = MIN(left + TS, width + 11);

      // Copy current tile from in to image buffer. If border goes
      // beyond edges of image, fill with mirrored/interpolated edges.
      // The extra border avoids discontinuities at image edges.
      for(int row = top; row < mrow; row++)
        for(int col = left; col < mcol; col++)
        {
          float(*const pix) = rgb[0][row - top][col - left];
          if((col >= 0) && (row >= 0) && (col < width) && (row < height))
          {
            const int f = FCxtrans(row + yoff, col + xoff, xtrans);
            for(int c = 0; c < 3; c++) pix[c] = (c == f) ? in[roi_in->width * row + col] : 0;
          }
          else
          {
            // mirror a border pixel if beyond image edge
            const int c = FCxtrans(row + yoff + 18, col + yoff + 18, xtrans);
            for(int cc = 0; cc < 3; cc++)
              if(cc != c)
                pix[cc] = 0.0f;
              else
              {
#define TRANSLATE(n, size) ((n >= size) ? (2 * size - n - 1) : abs(n))
                const int cy = TRANSLATE(row, height), cx = TRANSLATE(col, width);
                if(c == FCxtrans(cy + yoff, cx + xoff, xtrans))
                  pix[c] = in[roi_in->width * cy + cx];
                else
                {
                  // interpolate if mirror pixel is a different color
                  float sum = 0.0f;
                  uint8_t count = 0;
                  for(int y = row - 1; y <= row + 1; y++)
                    for(int x = col - 1; x <= col + 1; x++)
                    {
                      const int yy = TRANSLATE(y, height), xx = TRANSLATE(x, width);
                      const int ff = FCxtrans(yy + yoff, xx + xoff, xtrans);
                      if(ff == c)
                      {
                        sum += in[roi_in->width * yy + xx];
                        count++;
                      }
                    }
                  pix[c] = sum / count;
                }
              }
          }
        }

      // duplicate rgb[0] to rgb[1], rgb[2], and rgb[3]
      for(int c = 1; c <= 3; c++) memcpy(rgb[c], rgb[0], sizeof(*rgb));

      // note that successive calculations are inset within the tile
      // so as to give enough border data, and there needs to be a 6
      // pixel border initially to allow allhex to find neighboring
      // pixels

      /* Set green1 and green3 to the minimum and maximum allowed values:   */
      // Run through each red/blue or blue/red pair, setting their g1
      // and g3 values to the min/max of green pixels surrounding the
      // pair. Use a 3 pixel border as gmin/gmax is used by
      // interpolate green which has a 3 pixel border.
      for(int row = top + 3; row < mrow - 3; row++)
      {
        // setting max to 0.0f signifies that this is a new pair, which
        // requires a new min/max calculation of its neighboring greens
        float min = FLT_MAX, max = 0.0f;
        for(int col = left + 3; col < mcol - 3; col++)
        {
          // if in row of horizontal red & blue pairs (or processing
          // vertical red & blue pairs near image bottom), reset min/max
          // between each pair
          if(FCxtrans(yoff + row + 12, xoff + col + 12, xtrans) == 1)
          {
            min = FLT_MAX, max = 0.0f;
            continue;
          }
          // if at start of red & blue pair, calculate min/max of green
          // pixels surrounding it; note that while normally using == to
          // compare floats is suspect, here the check is if 0.0f has
          // explicitly been assigned to max (which signifies a new
          // red/blue pair)
          if(max == 0.0f)
          {
            float (*const pix)[3] = &rgb[0][row - top][col - left];
            const short *const hex = allhex[(row + 12) % 3][(col + 12) % 3];
            for(int c = 0; c < 6; c++)
            {
              const float val = pix[hex[c]][1];
              if(min > val) min = val;
              if(max < val) max = val;
            }
          }
          gmin[row - top][col - left] = min;
          gmax[row - top][col - left] = max;
          // handle vertical red/blue pairs
          switch((row - sgrow) % 3)
          {
            // hop down a row to second pixel in vertical pair
            case 1:
              if(row < mrow - 4) row++, col--;
              break;
            // then if not done with the row hop up and right to next
            // vertical red/blue pair, resetting min/max
            case 2:
              min = FLT_MAX, max = 0.0f;
              if((col += 2) < mcol - 4 && row > top + 3) row--;
          }
        }
      }

      /* Interpolate green horizontally, vertically, and along both diagonals: */
      // need a 3 pixel border here as 3*hex[] can have a 3 unit offset
      for(int row = top + 3; row < mrow - 3; row++)
        for(int col = left + 3; col < mcol - 3; col++)
        {
          float color[8];
          int f = FCxtrans(row + yoff + 12, col + xoff + 12, xtrans);
          if(f == 1) continue;
          float (*const pix)[3] = &rgb[0][row - top][col - left];
          short *hex = allhex[(row + 9) % 3][(col + 9) % 3];
          // TODO: these constants come from integer math constants in
          // dcraw -- calculate them instead from interpolation math
          color[0] = 0.6796875f * (pix[hex[1]][1] + pix[hex[0]][1])
                     - 0.1796875f * (pix[2 * hex[1]][1] + pix[2 * hex[0]][1]);
          color[1] = 0.87109375f * pix[hex[3]][1] + pix[hex[2]][1] * 0.13f
                     + 0.359375f * (pix[0][f] - pix[-hex[2]][f]);
          for(int c = 0; c < 2; c++)
            color[2 + c] = 0.640625f * pix[hex[4 + c]][1] + 0.359375f * pix[-2 * hex[4 + c]][1]
                           + 0.12890625f * (2 * pix[0][f] - pix[3 * hex[4 + c]][f] - pix[-3 * hex[4 + c]][f]);
          for(int c = 0; c < 4; c++)
            rgb[c ^ !((row - sgrow) % 3)][row - top][col - left][1]
                = CLAMPS(color[c], gmin[row - top][col - left], gmax[row - top][col - left]);
        }

      for(int pass = 0; pass < passes; pass++)
      {
        if(pass == 1)
        {
          // if on second pass, copy rgb[0] to [3] into rgb[4] to [7],
          // and process that second set of buffers
          memcpy(rgb + 4, rgb, (size_t)4 * sizeof(*rgb));
          rgb += 4;
        }

        /* Recalculate green from interpolated values of closer pixels: */
        if(pass)
          for(int row = top + 5; row < mrow - 5; row++)
            for(int col = left + 5; col < mcol - 5; col++)
            {
              int f = FCxtrans(row + yoff + 12, col + xoff + 12, xtrans);
              if(f == 1) continue;
              short *hex = allhex[(row + 12) % 3][(col + 12) % 3];
              for(int d = 3; d < 6; d++)
              {
                float(*rfx)[3] = &rgb[(d - 2) ^ !((row - sgrow) % 3)][row - top][col - left];
                float val = rfx[-2 * hex[d]][1] + 2 * rfx[hex[d]][1] - rfx[-2 * hex[d]][f]
                            - 2 * rfx[hex[d]][f] + 3 * rfx[0][f];
                rfx[0][1] = CLAMPS(val / 3.0f, gmin[row - top][col - left], gmax[row - top][col - left]);
              }
            }

        /* Interpolate red and blue values for solitary green pixels:   */
        for(int row = (top - sgrow + 7) / 3 * 3 + sgrow; row < mrow - 5; row += 3)
          for(int col = (left - sgcol + 7) / 3 * 3 + sgcol; col < mcol - 5; col += 3)
          {
            float(*rfx)[3] = &rgb[0][row - top][col - left];
            int h = FCxtrans(row + yoff + 12, col + xoff + 13, xtrans);
            float diff[6] = { 0.0f };
            float color[3][8];
            for(int i = 1, d = 0; d < 6; d++, i ^= TS ^ 1, h ^= 2)
            {
              for(int c = 0; c < 2; c++, h ^= 2)
              {
                float g = 2 * rfx[0][1] - rfx[i << c][1] - rfx[-i << c][1];
                color[h][d] = g + rfx[i << c][h] + rfx[-i << c][h];
                if(d > 1)
                  diff[d] += SQR(rfx[i << c][1] - rfx[-i << c][1] - rfx[i << c][h] + rfx[-i << c][h])
                             + SQR(g);
              }
              if(d > 1 && (d & 1))
                if(diff[d - 1] < diff[d])
                  for(int c = 0; c < 2; c++) color[c * 2][d] = color[c * 2][d - 1];
              if(d < 2 || (d & 1))
              {
                for(int c = 0; c < 2; c++) rfx[0][c * 2] = CLIPF(color[c * 2][d] / 2);
                rfx += TS * TS;
              }
            }
          }

        /* Interpolate red for blue pixels and vice versa:              */
        for(int row = top + 4; row < mrow - 4; row++)
          for(int col = left + 4; col < mcol - 4; col++)
          {
            int f = 2 - FCxtrans(row + yoff + 12, col + xoff + 12, xtrans);
            if(f == 1) continue;
            float(*rfx)[3] = &rgb[0][row - top][col - left];
            int i = (row - sgrow) % 3 ? TS : 1;
            for(int d = 0; d < 4; d++, rfx += TS * TS)
              rfx[0][f] = CLIPF((rfx[i][f] + rfx[-i][f] + 2 * rfx[0][1] - rfx[i][1] - rfx[-i][1]) / 2);
          }

        /* Fill in red and blue for 2x2 blocks of green:                */
        for(int row = top + 5; row < mrow - 5; row++)
          if((row - sgrow) % 3)
            for(int col = left + 5; col < mcol - 5; col++)
              if((col - sgcol) % 3)
              {
                float(*rfx)[3] = &rgb[0][row - top][col - left];
                short *hex = allhex[(row + 12) % 3][(col + 12) % 3];
                for(int d = 0; d < ndir; d += 2, rfx += TS * TS)
                  if(hex[d] + hex[d + 1])
                  {
                    float g = 3 * rfx[0][1] - 2 * rfx[hex[d]][1] - rfx[hex[d + 1]][1];
                    for(int c = 0; c < 4; c += 2)
                      rfx[0][c] = CLIPF((g + 2 * rfx[hex[d]][c] + rfx[hex[d + 1]][c]) / 3);
                  }
                  else
                  {
                    float g = 2 * rfx[0][1] - rfx[hex[d]][1] - rfx[hex[d + 1]][1];
                    for(int c = 0; c < 4; c += 2)
                      rfx[0][c] = CLIPF((g + rfx[hex[d]][c] + rfx[hex[d + 1]][c]) / 2);
                  }
              }
      } // end of multipass loop

      // jump back to the first set of rgb buffers (this is a nop
      // unless on the second pass)
      rgb = (float(*)[TS][TS][3])buffer;
      // from here on out, mainly are working within the current tile
      // rather than in reference to the image, so don't offset
      // mrow/mcol by top/left of tile
      mrow -= top;
      mcol -= left;

      /* Convert to perceptual colorspace and differentiate in all directions:  */
      // Original dcraw algorithm uses CIELab as perceptual space
      // (presumably coming from original AHD) and converts taking
      // camera matrix into account. Now use YPbPr which requires much
      // less code and is nearly indistinguishable. It assumes the
      // camera RGB is roughly linear.
      for(int d = 0; d < ndir; d++)
      {
        for(int row = 7; row < mrow - 7; row++)
          for(int col = 7; col < mcol - 7; col++)
          {
            float *rx = rgb[d][row][col];
            // use ITU-R BT.2020 YPbPr, which is great, but could use
            // a better/simpler choice? note that imageop.h provides
            // dt_iop_RGB_to_YCbCr which uses Rec. 601 conversion,
            // which appears less good with specular highlights
            float y = 0.2627f * rx[0] + 0.6780f * rx[1] + 0.0593f * rx[2];
            yuv[0][row][col] = y;
            yuv[1][row][col] = (rx[2] - y) * 0.56433f;
            yuv[2][row][col] = (rx[0] - y) * 0.67815f;
          }
        const int f = dir[d & 3];
        for(int row = 8; row < mrow - 8; row++)
          for(int col = 8; col < mcol - 8; col++)
          {
            float(*yfx)[TS][TS] = (float(*)[TS][TS]) & yuv[0][row][col];
            drv[d][row][col] = SQR(2 * yfx[0][0][0] - yfx[0][0][f] - yfx[0][0][-f])
                               + SQR(2 * yfx[1][0][0] - yfx[1][0][f] - yfx[1][0][-f])
                               + SQR(2 * yfx[2][0][0] - yfx[2][0][f] - yfx[2][0][-f]);
          }
      }

      /* Build homogeneity maps from the derivatives:                   */
      memset(homo, 0, (size_t)ndir * TS * TS * sizeof(uint8_t));
      for(int row = 9; row < mrow - 9; row++)
        for(int col = 9; col < mcol - 9; col++)
        {
          float tr = FLT_MAX;
          for(int d = 0; d < ndir; d++)
            if(tr > drv[d][row][col]) tr = drv[d][row][col];
          tr *= 8;
          for(int d = 0; d < ndir; d++)
            for(int v = -1; v <= 1; v++)
              for(int h = -1; h <= 1; h++) homo[d][row][col] += ((drv[d][row + v][col + h] <= tr) ? 1 : 0);
        }

      /* Build 5x5 sum of homogeneity maps for each pixel & direction */
      for(int d = 0; d < ndir; d++)
        for(int row = 11; row < mrow - 11; row++)
        {
          int col = 11;
          uint8_t v5sum[5] = { 0 };
          for(int v = -2; v <= 2; v++)
            for(int h = -2; h <= 2; h++) v5sum[(col + h) % 5] += homo[d][row + v][col + h];
          homosum[d][row][col] = v5sum[0] + v5sum[1] + v5sum[2] + v5sum[3] + v5sum[4];
          // calculate by rolling through column sums
          for(col++; col < mcol - 11; col++)
          {
            uint8_t colsum = 0;
            for(int v = -2; v <= 2; v++) colsum += homo[d][row + v][col + 2];
            homosum[d][row][col] = homosum[d][row][col - 1] - v5sum[col % 5] + colsum;
            v5sum[col % 5] = colsum;
          }
        }

      /* Average the most homogenous pixels for the final result:       */
      for(int row = 11; row < mrow - 11; row++)
        for(int col = 11; col < mcol - 11; col++)
        {
          uint8_t hm[8] = { 0 };
          uint8_t maxval = 0;
          for(int d = 0; d < ndir; d++)
          {
            hm[d] = homosum[d][row][col];
            maxval = (maxval < hm[d] ? hm[d] : maxval);
          }
          maxval -= maxval >> 3;
          for(int d = 0; d < ndir - 4; d++)
            if(hm[d] < hm[d + 4])
              hm[d] = 0;
            else if(hm[d] > hm[d + 4])
              hm[d + 4] = 0;
          float avg[4] = { 0.0f };
          for(int d = 0; d < ndir; d++)
            if(hm[d] >= maxval)
            {
              for(int c = 0; c < 3; c++) avg[c] += rgb[d][row][col][c];
              avg[3]++;
            }
          for(int c = 0; c < 3; c++) out[4 * (width * (row + top) + col + left) + c] = avg[c] / avg[3];
        }
    }
  }
  free(all_buffers);
}
