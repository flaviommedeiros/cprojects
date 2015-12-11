#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T0ACMBEXT(GR_CMBX_ITALPHA, GR_FUNC_MODE_X,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_TMU_CALPHA, 0,
            GR_CMBX_B, 0);
      cmb.tex |= 1;
      cmb.tex_ccolor = (cmb.tex_ccolor&0xFFFFFF00) | (g_gdp.prim_color.total&0xFF);
      ACMBEXT(GR_CMBX_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ZERO, GR_FUNC_MODE_ZERO,
            GR_CMBX_ITALPHA, 0,
            GR_CMBX_ZERO, 0);
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ACMB (GR_COMBINE_FUNCTION_SCALE_OTHER_ADD_LOCAL,
            GR_COMBINE_FACTOR_ONE,
            GR_COMBINE_LOCAL_ITERATED,
            GR_COMBINE_OTHER_TEXTURE);
      MULSHADE_A_PRIM();
      A_USE_T0();
   }
