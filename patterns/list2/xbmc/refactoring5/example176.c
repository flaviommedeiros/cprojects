#ifdef TT_CONFIG_OPTION_UNPATENTED_HINTING
if ( CUR.face->unpatented_hinting )
    {
      if ( CUR.GS.both_x_axis )
      {
        dx = TT_MulFix14( args[0], 0x4000 );
        dy = 0;
      }
      else
      {
        dx = 0;
        dy = TT_MulFix14( args[0], 0x4000 );
      }
    }
    else
#endif
    {
      dx = TT_MulFix14( args[0], CUR.GS.freeVector.x );
      dy = TT_MulFix14( args[0], CUR.GS.freeVector.y );
    }
