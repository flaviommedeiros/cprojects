#ifdef RE_ENABLE_I18N
if (dfa->mb_cur_max > 1)
	build_wcs_buffer (pstr);
      else
#endif /* RE_ENABLE_I18N  */
	{
	  if (trans != NULL)
	    re_string_translate_buffer (pstr);
	  else
	    {
	      pstr->valid_len = pstr->bufs_len;
	      pstr->valid_raw_len = pstr->bufs_len;
	    }
	}
