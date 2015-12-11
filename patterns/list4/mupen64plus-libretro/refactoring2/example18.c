#ifndef HAVE_ASSUME_COMBINE_EXT
if (cmb.combine_ext)
#endif
   {
      ACMBEXT(GR_CMBX_CONSTANT_ALPHA, GR_FUNC_MODE_X,
            GR_CMBX_ITALPHA, GR_FUNC_MODE_NEGATIVE_X,
            GR_CMBX_CONSTANT_ALPHA, 0,
            GR_CMBX_ZERO, 0);
      CA_PRIM();
   }
#ifndef HAVE_ASSUME_COMBINE_EXT
   else
   {
      if (!(g_gdp.prim_color.total & 0xFF))
      {
         ac_zero();
      }
      else
      {
         ACMB (GR_COMBINE_FUNCTION_SCALE_OTHER_MINUS_LOCAL,
               GR_COMBINE_FACTOR_ONE,
               GR_COMBINE_LOCAL_ITERATED,
               GR_COMBINE_OTHER_CONSTANT);
         CA_PRIM();
      }
   }
