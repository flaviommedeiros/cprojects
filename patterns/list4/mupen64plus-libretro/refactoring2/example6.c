#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T0CCMBEXT(GR_CMBX_LOCAL_TEXTURE_RGB, GR_FUNC_MODE_X,
            GR_CMBX_TMU_CCOLOR, GR_FUNC_MODE_ZERO,
            GR_CMBX_TMU_CCOLOR, 0,
            GR_CMBX_ZERO, 0);
      cmb.tex |= 1;
      cmb.tex_ccolor = g_gdp.prim_color.total;
      CCMBEXT(GR_CMBX_ITRGB, GR_FUNC_MODE_X,
            GR_CMBX_TEXTURE_RGB, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_CONSTANT_COLOR, 0,
            GR_CMBX_B, 0);
      SETSHADE_ENV();
      CC_ENVA();
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
  else
  {
     CCMB (GR_COMBINE_FUNCTION_SCALE_OTHER,
           GR_COMBINE_FACTOR_LOCAL,
           GR_COMBINE_LOCAL_ITERATED,
           GR_COMBINE_OTHER_TEXTURE);
     SETSHADE_PRIM();
     INTERSHADE_2 (g_gdp.env_color, g_gdp.env_color.a);
     USE_T0();
     MOD_0 (TMOD_TEX_INTER_COLOR_USING_FACTOR);
     MOD_0_COL (g_gdp.env_color.total & 0xFFFFFF00);
     MOD_0_FAC (g_gdp.env_color.total & 0xFF);
  }
