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
      cmb.tex_ccolor = (cmb.tex_ccolor&0xFFFFFF00) | (0xFF) ;
      cmb.tex |= 3;
      cmb.dc0_detailmax = cmb.dc1_detailmax = (g_gdp.env_color.total&0xFF) / 255.0f;
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      // (t1-1)*env+t0, (cmb-0)*prim+0
      A_T0_MUL_T1();

      MOD_1 (TMOD_TEX_SCALE_FAC_ADD_FAC);
      MOD_1_FAC (g_gdp.env_color.total & 0xFF);
   }
