#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T1CCMBEXT(GR_CMBX_LOCAL_TEXTURE_RGB, GR_FUNC_MODE_ZERO,
            GR_CMBX_LOCAL_TEXTURE_RGB, GR_FUNC_MODE_ZERO,
            GR_CMBX_ZERO, 0,
            GR_CMBX_B, 0);
      T0CCMBEXT(GR_CMBX_LOCAL_TEXTURE_RGB, GR_FUNC_MODE_X,
            GR_CMBX_OTHER_TEXTURE_RGB, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_B, 0,
            GR_CMBX_B, 0);
      cmb.tex |= 3;
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      T0_INTER_T1_USING_FACTOR (0x7F);
   }
