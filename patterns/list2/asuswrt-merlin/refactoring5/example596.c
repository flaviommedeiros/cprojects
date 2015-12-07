#ifdef RE_ENABLE_I18N
if (dfa->mb_cur_max > 1)
	{
	  while (1)
	    {
	      ret = build_wcs_upper_buffer (pstr);
	      if (BE (ret != REG_NOERROR, 0))
		return ret;
	      if (pstr->valid_raw_len >= len)
		break;
	      if (pstr->bufs_len > pstr->valid_len + dfa->mb_cur_max)
		break;
	      ret = re_string_realloc_buffers (pstr, pstr->bufs_len * 2);
	      if (BE (ret != REG_NOERROR, 0))
		return ret;
	    }
	}
      else
#endif /* RE_ENABLE_I18N  */
	build_upper_buffer (pstr);
