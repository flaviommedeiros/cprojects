void dt_iop_clip_and_zoom_demosaic_third_size_xtrans(float *out, const uint16_t *const in,
                                                     const dt_iop_roi_t *const roi_out,
                                                     const dt_iop_roi_t *const roi_in,
                                                     const int32_t out_stride, const int32_t in_stride,
                                                     const uint8_t (*const xtrans)[6])
{
  const float px_footprint = 1.f / roi_out->scale;
  const int samples = round(px_footprint / 3);

#ifdef _OPENMP
#pragma omp parallel for default(none) shared(out) schedule(static)
#endif
  for(int y = 0; y < roi_out->height; y++)
  {
    float *outc = out + (size_t)4 * (out_stride * y);

    int py = floorf((y + roi_out->y) * px_footprint);
    py = MIN(roi_in->height - 4, py);
    int maxj = MIN(roi_in->height - 3, py + 3 * samples);

    float fx = roi_out->x * px_footprint;
    for(int x = 0; x < roi_out->width; x++, fx += px_footprint)
    {
      int px = floorf(fx);
      px = MIN(roi_in->width - 4, px);
      int maxi = MIN(roi_in->width - 3, px + 3 * samples);

      uint16_t pc = 0;
      for(int ii = 0; ii < 3; ++ii)
        for(int jj = 0; jj < 3; ++jj) pc = MAX(pc, in[px + ii + in_stride * (py + jj)]);

      uint8_t num[3] = { 0 };
      uint32_t sum[3] = { 0 };

      for(int j = py; j <= maxj; j += 3)
        for(int i = px; i <= maxi; i += 3)
        {
          uint16_t lcl_max = 0;
          for(int ii = 0; ii < 3; ++ii)
            for(int jj = 0; jj < 3; ++jj) lcl_max = MAX(lcl_max, in[i + ii + in_stride * (j + jj)]);

          if(!((pc >= 60000) ^ (lcl_max >= 60000)))
          {
            for(int ii = 0; ii < 3; ++ii)
              for(int jj = 0; jj < 3; ++jj)
              {
                const uint8_t c = FCxtrans(j + jj, i + ii, roi_in, xtrans);
                sum[c] += in[i + ii + in_stride * (j + jj)];
                num[c]++;
              }
          }
        }

      outc[0] = sum[0] / 65535.0f / num[0];
      outc[1] = sum[1] / 65535.0f / num[1];
      outc[2] = sum[2] / 65535.0f / num[2];
      outc += 4;
    }
  }
}
