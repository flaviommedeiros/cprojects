#ifdef HAVE_SYSTEM_TZDATA
if (memmap) {
			const struct location_info *li;

			/* TZif-style - grok the location info from the system database,
			 * if possible. */

			if ((li = find_zone_info(system_location_table, timezone)) != NULL) {
				tmp->location.comments = strdup(li->comment);
                                strncpy(tmp->location.country_code, li->code, 2);
				tmp->location.longitude = li->longitude;
				tmp->location.latitude = li->latitude;
				tmp->bc = 1;
			}
			else {
				strcpy(tmp->location.country_code, "??");
				tmp->bc = 0;
				tmp->location.comments = strdup("");
			}

			/* Now done with the mmap segment - discard it. */
			munmap(memmap, maplen);
		} else
#endif
		{
			/* PHP-style - use the embedded info. */
			read_location(&tzf, tmp);
		}
