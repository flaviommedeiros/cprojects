#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T1ACMBEXT(GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_ZERO, 0,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, 0);
      T0ACMBEXT(GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_OTHER_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_TMU_CALPHA, 0,
            GR_CMBX_B, 0);
      cmb.tex_ccolor = (cmb.tex_ccolor&0xFFFFFF00) | (g_gdp.env_color.total&0xFF) ;
      cmb.tex |= 3;
      ACMB (GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL,
            GR_COMBINE_FACTOR_ONE,
            GR_COMBINE_LOCAL_CONSTANT,
            GR_COMBINE_OTHER_TEXTURE);
      CA_ENV();
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ac__t0_mul_t1__mul_env();
   }
