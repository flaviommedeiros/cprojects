#ifdef TT_CONFIG_OPTION_UNPATENTED_HINTING
if ( CUR.face->unpatented_hinting )
      {
        if ( CUR.GS.both_x_axis )
          CUR.tt_metrics.ratio = CUR.tt_metrics.x_ratio;
        else
          CUR.tt_metrics.ratio = CUR.tt_metrics.y_ratio;
      }
      else
#endif
      {
        if ( CUR.GS.projVector.y == 0 )
          CUR.tt_metrics.ratio = CUR.tt_metrics.x_ratio;

        else if ( CUR.GS.projVector.x == 0 )
          CUR.tt_metrics.ratio = CUR.tt_metrics.y_ratio;

        else
        {
          FT_F26Dot6  x, y;


          x = TT_MulFix14( CUR.tt_metrics.x_ratio,
                           CUR.GS.projVector.x );
          y = TT_MulFix14( CUR.tt_metrics.y_ratio,
                           CUR.GS.projVector.y );
          CUR.tt_metrics.ratio = FT_Hypot( x, y );
        }
      }
