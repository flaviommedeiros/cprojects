#ifdef TT_CONFIG_OPTION_UNPATENTED_HINTING
if ( CUR.face->unpatented_hinting )
    {
      if ( CUR.GS.both_x_axis )
      {
        dx = (FT_UInt32)args[0];
        dy = 0;
      }
      else
      {
        dx = 0;
        dy = (FT_UInt32)args[0];
      }
    }
    else
#endif
    {
      dx = TT_MulFix14( (FT_UInt32)args[0], CUR.GS.freeVector.x );
      dy = TT_MulFix14( (FT_UInt32)args[0], CUR.GS.freeVector.y );
    }
