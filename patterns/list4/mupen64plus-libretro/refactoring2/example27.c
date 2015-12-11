#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      ACMBEXT(GR_CMBX_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ITALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_ZERO, 1,
            GR_CMBX_ZERO, 0);
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ACMB (GR_COMBINE_FUNCTION_SCALE_OTHER,
            GR_COMBINE_FACTOR_ONE,
            GR_COMBINE_LOCAL_NONE,
            GR_COMBINE_OTHER_TEXTURE);
   }
