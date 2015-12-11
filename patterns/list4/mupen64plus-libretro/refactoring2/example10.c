#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T0ACMBEXT(GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ITALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_DETAIL_FACTOR, 0,
            GR_CMBX_B, 0);
      cmb.tex |= 1;
      percent = lod_frac / 255.0f;
      cmb.dc0_detailmax = cmb.dc1_detailmax = percent;
      ACMBEXT(GR_CMBX_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ZERO, GR_FUNC_MODE_ZERO,
            GR_CMBX_ITALPHA, 0,
            GR_CMBX_ZERO, 0);
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ACMB (GR_COMBINE_FUNCTION_SCALE_OTHER,
            GR_COMBINE_FACTOR_LOCAL,
            GR_COMBINE_LOCAL_ITERATED,
            GR_COMBINE_OTHER_TEXTURE);
      A_USE_T0();
   }
