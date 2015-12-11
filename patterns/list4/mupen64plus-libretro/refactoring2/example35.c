#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T0ACMBEXT(GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_TMU_CALPHA, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_DETAIL_FACTOR, 0,
            GR_CMBX_B, 0);
      cmb.tex_ccolor = (cmb.tex_ccolor&0xFFFFFF00) | (0xFF) ;
      cmb.tex |= 1;
      cmb.dc0_detailmax = cmb.dc1_detailmax = (g_gdp.prim_color.total&0xFF) / 255.0f;
      ACMBEXT(GR_CMBX_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_CONSTANT_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_CONSTANT_ALPHA, 0,
            GR_CMBX_ZERO, 0);
      CA_ENV();
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ac_t0_mul_prim_add_env();
   }
