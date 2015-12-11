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
      *x = TT_MULDIV( d,
                      (FT_Long)CUR.GS.freeVector.x * 0x10000L,
                      CUR.F_dot_P );
      *y = TT_MULDIV( d,
                      (FT_Long)CUR.GS.freeVector.y * 0x10000L,
                      CUR.F_dot_P );
    }
