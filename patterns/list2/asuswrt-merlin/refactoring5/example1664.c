#ifdef RE_ENABLE_I18N
if (pstr->mb_cur_max > 1)
	{
	  ret = build_wcs_upper_buffer (pstr);
	  if (BE (ret != REG_NOERROR, 0))
	    return ret;
	}
      else
#endif /* RE_ENABLE_I18N  */
	build_upper_buffer (pstr);
