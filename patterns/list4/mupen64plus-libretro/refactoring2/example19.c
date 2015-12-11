#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      ACMBEXT(GR_CMBX_ZERO, GR_FUNC_MODE_ONE_MINUS_X,
            GR_CMBX_CONSTANT_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ITALPHA, 0,
            GR_CMBX_ZERO, 0);
      MULSHADE_A_PRIM();
      CA_ENV();
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ac_prim_mul_shade();
   }
