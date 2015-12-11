#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T0CCMBEXT(GR_CMBX_LOCAL_TEXTURE_RGB, GR_FUNC_MODE_X,
            GR_CMBX_LOCAL_TEXTURE_RGB, GR_FUNC_MODE_ZERO,
            GR_CMBX_ITRGB, 0,
            GR_CMBX_ZERO, 0);
      cmb.tex |= 1;
      CCMBEXT(GR_CMBX_ITRGB, GR_FUNC_MODE_ZERO,
            GR_CMBX_TEXTURE_RGB, GR_FUNC_MODE_X,
            GR_CMBX_ZERO, 1,
            GR_CMBX_B, 0);
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      CCMB (GR_COMBINE_FUNCTION_SCALE_OTHER,
            GR_COMBINE_FACTOR_LOCAL,
            GR_COMBINE_LOCAL_ITERATED,
            GR_COMBINE_OTHER_TEXTURE);
      USE_T0();
   }
