static int process_xtrans(const void *const i, void *o, const dt_iop_roi_t *const roi_in, const int width,
                          const int height, const uint8_t (*const xtrans)[6], const float threshold,
                          const float multiplier, const gboolean markfixed, const int min_neighbours)
{
  // for each cell of sensor array, a list of the x/y offsets of the
  // four radially nearest pixels of the same color
  int offsets[6][6][4][2];
  const int search[20][2] = { { -1, 0 },
                              { 1, 0 },
                              { 0, -1 },
                              { 0, 1 },
                              { -1, -1 },
                              { -1, 1 },
                              { 1, -1 },
                              { 1, 1 },
                              { -2, 0 },
                              { 2, 0 },
                              { 0, -2 },
                              { 0, 2 },
                              { -2, -1 },
                              { -2, 1 },
                              { 2, -1 },
                              { 2, 1 },
                              { -1, -2 },
                              { 1, -2 },
                              { -1, 2 },
                              { 1, 2 } };
  for(int j = 0; j < 6; ++j)
    for(int i = 0; i < 6; ++i)
    {
      const uint8_t c = FCxtrans(j, i, roi_in, xtrans);
      for(int s = 0, found = 0; s < 20 && found < 4; ++s)
      {
        if(c == FCxtrans(j + search[s][1], i + search[s][0], roi_in, xtrans))
        {
          offsets[i][j][found][0] = search[s][0];
          offsets[i][j][found][1] = search[s][1];
          ++found;
        }
      }
    }

  int fixed = 0;
#ifdef _OPENMP
#pragma omp parallel for default(none) shared(o, offsets) reduction(+ : fixed) schedule(static)
#endif
  for(int row = 1; row < height - 1; row++)
  {
    const float *in = (float *)i + (size_t)width * row + 2;
    float *out = (float *)o + (size_t)width * row + 2;
    for(int col = 1; col < width - 1; col++, in++, out++)
    {
      float mid = *in * multiplier;
      if(*in > threshold)
      {
        int count = 0;
        float maxin = 0.0;
        for(int n = 0; n < 4; ++n)
        {
          int xx = offsets[col % 6][row % 6][n][0];
          int yy = offsets[col % 6][row % 6][n][1];
          if((xx < -col) || (xx >= (width - col)) || (yy < -row) || (yy >= (height - row))) break;
          float other = *(in + xx + yy * width);
          if(mid > other)
          {
            count++;
            if(other > maxin) maxin = other;
          }
        }
        // NOTE: it seems that detecting by 2 neighbors would help for extreme cases
        if(count >= min_neighbours)
        {
          *out = maxin;
          fixed++;
          if(markfixed)
          {
            // cheat and mark all colors of pixels
            // FIXME: use offsets
            for(int i = -2; i >= -10 && i >= -col; --i) out[i] = *in;
            for(int i = 2; i <= 10 && i < width - col; ++i) out[i] = *in;
          }
        }
      }
    }
  }

  return fixed;
}
