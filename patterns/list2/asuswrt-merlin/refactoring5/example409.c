#ifdef _NL_CURRENT
if (era_cnt != -1)
    {
      era = _nl_select_era_entry(era_cnt);
      if (want_era)
	tm->tm_year = (era->start_date[0]
		       + ((tm->tm_year - era->offset)
			  * era->absolute_direction));
      else
	/* Era start year assumed.  */
	tm->tm_year = era->start_date[0];
    }
  else
#endif
    if (want_era)
      return NULL;
