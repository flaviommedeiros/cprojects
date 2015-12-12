if (now >= dev->bid_time &&
#ifdef HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC
	    (st.st_mtime < dev->bid_time ||
	        (st.st_mtime == dev->bid_time &&
		 st.st_mtim.tv_nsec / 1000 <= dev->bid_utime)) &&
#else
	    st.st_mtime <= dev->bid_time &&
#endif
	    (diff < BLKID_PROBE_MIN ||
		(dev->bid_flags & BLKID_BID_FL_VERIFIED &&
		 diff < BLKID_PROBE_INTERVAL)))
		return dev;
