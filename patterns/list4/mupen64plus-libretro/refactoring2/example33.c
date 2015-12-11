#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      ACMBEXT(GR_CMBX_ZERO, GR_FUNC_MODE_ZERO,
            GR_CMBX_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_CONSTANT_ALPHA, 0,
            GR_CMBX_B, 0);
      CA_ENV();
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ACMB (GR_COMBINE_FUNCTION_BLEND,
            GR_COMBINE_FACTOR_TEXTURE_ALPHA,
            GR_COMBINE_LOCAL_CONSTANT,
            GR_COMBINE_OTHER_ITERATED);
      SETSHADE_A_ENV();
      CA (0xFF);
   }
