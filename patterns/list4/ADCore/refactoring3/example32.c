switch (format) {
#ifdef USE_NETCDF4
	 case NC_FORMAT_NETCDF4:
	    xcmode |= NC_NETCDF4;
	    model = NC_DISPATCH_NC4;
	    break;
	 case NC_FORMAT_NETCDF4_CLASSIC:
	    xcmode |= NC_CLASSIC_MODEL;
	    model = NC_DISPATCH_NC4;
	    break;
#endif
	 case NC_FORMAT_64BIT:
	    xcmode |= NC_64BIT_OFFSET;
	    /* fall thru */
	 case NC_FORMAT_CLASSIC:
	 default:
	    model = NC_DISPATCH_NC3;
	    break;
      }
