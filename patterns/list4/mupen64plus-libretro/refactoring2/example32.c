#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      ACMBEXT(GR_CMBX_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_CONSTANT_ALPHA, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_ITALPHA, 0,
            GR_CMBX_ALOCAL, 0);
      CA_ENV();
      A_T0_INTER_T1_USING_FACTOR (lod_frac);
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ac__t0_inter_t1_using_primlod__mul_shade();
   }
