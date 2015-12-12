switch (keyinfo->key_alg)
  {
#ifdef HAVE_RTREE_KEYS
    case HA_KEY_ALG_RTREE:
      if ((error=rtree_find_next(info,inx,
				 myisam_read_vec[info->last_key_func])))
      {
	error=1;
	my_errno=HA_ERR_END_OF_FILE;
	info->lastpos= HA_OFFSET_ERROR;
	break;
      }
      break;
#endif
    case HA_KEY_ALG_BTREE:
    default:

      if (info->set_rnext_same_key)
      {
        /* First rnext_same and lastkey is filled in mi_rkey */
        memcpy(info->rnext_same_key, info->lastkey, info->last_rkey_length);
        info->set_rnext_same_key= FALSE;
      }
      for (;;)
      {
        if ((error=_mi_search_next(info,keyinfo,info->lastkey,
			       info->lastkey_length,SEARCH_BIGGER,
			       info->s->state.key_root[inx])))
          break;
        if (ha_key_cmp(keyinfo->seg, info->lastkey, info->rnext_same_key,
                       info->last_rkey_length, SEARCH_FIND, not_used))
        {
          error=1;
          my_errno=HA_ERR_END_OF_FILE;
          info->lastpos= HA_OFFSET_ERROR;
          break;
        }
        /* Skip rows that are inserted by other threads since we got a lock */
        if (info->lastpos < info->state->data_file_length && 
            (!info->index_cond_func || mi_check_index_cond(info, inx, buf)))
          break;
      }
  }
