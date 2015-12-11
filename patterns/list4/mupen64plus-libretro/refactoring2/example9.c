#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T0ACMBEXT(GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_DETAIL_FACTOR, 0,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, 0);
      cmb.tex |= 1;
      percent = lod_frac / 255.0f;
      cmb.dc0_detailmax = cmb.dc1_detailmax = percent;
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      A_USE_T0();
   }
