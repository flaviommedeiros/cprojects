#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T1ACMBEXT(GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_ZERO, 0,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, 0);
      T0ACMBEXT(GR_CMBX_OTHER_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_TMU_CALPHA, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_DETAIL_FACTOR, 0,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, 0);
      cmb.tex_ccolor = (cmb.tex_ccolor&0xFFFFFF00) | 0xFF ;
      percent = (float)g_gdp.env_color.a;
      cmb.dc0_detailmax = cmb.dc1_detailmax = percent;
      cmb.tex |= 3;
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      uint8_t factor = (uint8_t)g_gdp.env_color.a;
      A_T0_INTER_T1_USING_FACTOR (factor);
   }
