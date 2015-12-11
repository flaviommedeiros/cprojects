#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T1ACMBEXT(GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_ZERO, 0,
            GR_CMBX_B, 0);
      T0ACMBEXT(GR_CMBX_OTHER_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ITALPHA, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_TMU_CALPHA, 0,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, 0);
      cmb.tex_ccolor = (cmb.tex_ccolor&0xFFFFFF00) | (g_gdp.env_color.total&0xFF) ;
      SETSHADE_A (0xFF);
      cmb.tex |= 3;
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
      A_USE_T0();
   }
