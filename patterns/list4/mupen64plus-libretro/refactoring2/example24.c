#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T0ACMBEXT(GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_ZERO, 1,
            GR_CMBX_ZERO, 0);
      cmb.tex |= 1;
      ACMBEXT(GR_CMBX_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_CONSTANT_ALPHA, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_ITALPHA, 0,
            GR_CMBX_B, 0);
      CA_ENV();
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ac_t0_mul_shade();
   }
