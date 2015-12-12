#ifdef HAVE_SYSTEM_TZDATA
if (tzdb == timezonedb_system) {
		char *orig;

		orig = map_tzfile(timezone, maplen);
		if (orig == NULL) {
			return 0;
		}

		(*tzf) = (unsigned char *)orig ;
		*map = orig;

                return 1;
	}
       else
#endif
       {
		return inmem_seek_to_tz_position(tzf, timezone, tzdb);
	}
