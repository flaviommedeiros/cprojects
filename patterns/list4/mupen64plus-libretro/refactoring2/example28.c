#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T1ACMBEXT(GR_CMBX_TMU_CALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ITALPHA, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, 0,
            GR_CMBX_ZERO, 0);
      T0ACMBEXT(GR_CMBX_OTHER_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ZERO, 1,
            GR_CMBX_ZERO, 0);
      SETSHADE_A(0xFF);
      cmb.tex_ccolor = (cmb.tex_ccolor&0xFFFFFF00) | (g_gdp.env_color.total&0xFF) ;
      cmb.tex |= 3;
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      uint8_t factor = g_gdp.env_color.a;
      A_T0_INTER_T1_USING_FACTOR (factor);
   }
