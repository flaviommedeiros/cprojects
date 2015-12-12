#ifdef RE_ENABLE_I18N
if (pstr->mb_cur_max > 1)
    {
      if (pstr->icase)
	{
	  reg_errcode_t ret = build_wcs_upper_buffer (pstr);
	  if (BE (ret != REG_NOERROR, 0))
	    return ret;
	}
      else
	build_wcs_buffer (pstr);
    }
  else
#endif /* RE_ENABLE_I18N */
    if (BE (pstr->mbs_allocated, 0))
      {
	if (pstr->icase)
	  build_upper_buffer (pstr);
	else if (pstr->trans != NULL)
	  re_string_translate_buffer (pstr);
      }
    else
      pstr->valid_len = pstr->len;
