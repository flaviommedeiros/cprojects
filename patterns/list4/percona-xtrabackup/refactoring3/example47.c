switch (info->s->keyinfo[inx].key_alg) {
#ifdef HAVE_RTREE_KEYS
  case HA_KEY_ALG_RTREE:
    if (rtree_find_first(info,inx,key_buff,use_key_length,nextflag) < 0)
    {
      mi_print_error(info->s, HA_ERR_CRASHED);
      my_errno=HA_ERR_CRASHED;
      if (share->concurrent_insert)
        mysql_rwlock_unlock(&share->key_root_lock[inx]);
      goto err;
    }
    break;
#endif
  case HA_KEY_ALG_BTREE:
  default:
    myisam_search_flag= myisam_read_vec[search_flag];
    if (!_mi_search(info, keyinfo, key_buff, use_key_length,
                    myisam_search_flag, info->s->state.key_root[inx]))
    {
      /*
        Found a key, but it might not be usable. We cannot use rows that
        are inserted by other threads after we got our table lock
        ("concurrent inserts"). The record may not even be present yet.
        Keys are inserted into the index(es) before the record is
        inserted into the data file. When we got our table lock, we
        saved the current data_file_length. Concurrent inserts always go
        to the end of the file. So we can test if the found key
        references a new record.

        If we are searching for a partial key (or using >, >=, < or <=) and
        the data is outside of the data file, we need to continue searching
        for the first key inside the data file.

        We do also continue searching if an index condition check function
        is available.
      */
      while ((info->lastpos >= info->state->data_file_length &&
              (search_flag != HA_READ_KEY_EXACT ||
              last_used_keyseg != keyinfo->seg + keyinfo->keysegs)) ||
             (info->index_cond_func && 
              !(res= mi_check_index_cond(info, inx, buf))))
      {
        uint not_used[2];
        /*
          Skip rows that are inserted by other threads since we got a lock
          Note that this can only happen if we are not searching after an
          full length exact key, because the keys are sorted
          according to position
        */
        if  (_mi_search_next(info, keyinfo, info->lastkey,
                             info->lastkey_length,
                             myisam_readnext_vec[search_flag],
                             info->s->state.key_root[inx]))
          break;
        /*
          Check that the found key does still match the search.
          _mi_search_next() delivers the next key regardless of its
          value.
        */
        if (search_flag == HA_READ_KEY_EXACT &&
            ha_key_cmp(keyinfo->seg, key_buff, info->lastkey, use_key_length,
                       SEARCH_FIND, not_used))
        {
          my_errno= HA_ERR_KEY_NOT_FOUND;
          info->lastpos= HA_OFFSET_ERROR;
          break;
        }
      }
      if (res == 2)
      {
        info->lastpos= HA_OFFSET_ERROR;
        if (share->concurrent_insert)
          mysql_rwlock_unlock(&share->key_root_lock[inx]);
        DBUG_RETURN((my_errno= HA_ERR_KEY_NOT_FOUND));
      }
      /*
        Error if no row found within the data file. (Bug #29838)
        Do not overwrite my_errno if already at HA_OFFSET_ERROR.
      */
      if (info->lastpos != HA_OFFSET_ERROR &&
          info->lastpos >= info->state->data_file_length)
      {
        info->lastpos= HA_OFFSET_ERROR;
        my_errno= HA_ERR_KEY_NOT_FOUND;
      }
    }
  }
