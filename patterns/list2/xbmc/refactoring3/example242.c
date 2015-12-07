switch( mode ) {

  case -1:  /* initialize */
    if ( last_mode != -1 ) {
      XCopyArea( xskin_d, xskin_back, xskin_w, xskin_gc,
		 SPE_SX, SPE_SY, SPE_W, SPE_H, SPE_SX, SPE_SY );
    }
    break;

  case 0:  /* blank */
    if ( last_mode != 0 ) {
      XCopyArea( xskin_d, xskin_back, xskin_w, xskin_gc,
		 SPE_SX, SPE_SY, SPE_W, SPE_H, SPE_SX, SPE_SY );
    }
    break;

#ifdef SUPPORT_SOUNDSPEC
  case 1:  /* spectrum analizer */
    xskin_spe_ana(buf);
    break;

  case 2:  /* wave form */
    xskin_wave(buf);
    break;
#endif /* SUPPORT_SOUNDSPEC */

  default:
    break;
  }
