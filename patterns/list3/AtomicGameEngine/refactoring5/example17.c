#ifdef TT_CONFIG_OPTION_UNPATENTED_HINTING
if ( CUR.face->unpatented_hinting )
    {
      if ( CUR.GS.both_x_axis )
      {
        *x = d;
        *y = 0;
      }
      else
      {
        *x = 0;
        *y = d;
      }
    }
    else
#endif
    {
      *x = FT_MulDiv( d, (FT_Long)CUR.GS.freeVector.x, CUR.F_dot_P );
      *y = FT_MulDiv( d, (FT_Long)CUR.GS.freeVector.y, CUR.F_dot_P );
    }
