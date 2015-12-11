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
      percent = lod_frac / 255.0f;
      cmb.dc0_detailmax = cmb.dc1_detailmax = percent;
      cmb.tex |= 3;
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      //    A_T0_MUL_T1();
      //    A_T1_MUL_PRIMLOD_ADD_T0();
      cmb.tmu1_a_func = GR_COMBINE_FUNCTION_BLEND_LOCAL;
      cmb.tmu1_a_fac = GR_COMBINE_FACTOR_DETAIL_FACTOR;
      percent = (255 - lod_frac) / 255.0f;
      cmb.tmu0_a_func = GR_COMBINE_FUNCTION_SCALE_MINUS_LOCAL_ADD_LOCAL_ALPHA;
      cmb.tmu0_a_fac = GR_COMBINE_FACTOR_OTHER_ALPHA;
      cmb.dc0_detailmax = cmb.dc1_detailmax = percent;
      cmb.tex |= 3;
   }
