#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      T0ACMBEXT(GR_CMBX_ITALPHA, GR_FUNC_MODE_X,
            GR_CMBX_LOCAL_TEXTURE_ALPHA, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_TMU_CALPHA, 0,
            GR_CMBX_ZERO, 0);
      cmb.tex_ccolor = (cmb.tex_ccolor&0xFFFFFF00) | (lod_frac&0xFF);
      cmb.tex |= 1;
      ACMBEXT(GR_CMBX_CONSTANT_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ITALPHA, GR_FUNC_MODE_ZERO,
            GR_CMBX_ZERO, 1,
            GR_CMBX_TEXTURE_ALPHA, 0);
      CA_PRIM();
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      ac_t0();
   }
