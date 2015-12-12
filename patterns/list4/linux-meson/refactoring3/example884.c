switch( cmd ) {
		// ================== Private IOCTLs (up to 16) ==================
#ifdef USE_UIL
	case WVLAN2_IOCTL_UIL:
	     DBG_TRACE( DbgInfo, "IOCTL: WVLAN2_IOCTL_UIL\n" );
	     ret = wvlan_uil( urq, lp );
	     break;
#endif  /* USE_UIL */

	default:
	     DBG_TRACE(DbgInfo, "IOCTL CODE NOT SUPPORTED: 0x%X\n", cmd );
	     ret = -EOPNOTSUPP;
	     break;
	}
