switch(info->s->keyinfo[inx].key_alg){
#ifdef HAVE_RTREE_KEYS
  case HA_KEY_ALG_RTREE:
  {
    uchar * key_buff;
    uint start_key_len;

    /*
      The problem is that the optimizer doesn't support
      RTree keys properly at the moment.
      Hope this will be fixed some day.
      But now NULL in the min_key means that we
      didn't make the task for the RTree key
      and expect BTree functionality from it.
      As it's not able to handle such request
      we return the error.
    */
    if (!min_key)
    {
      res= HA_POS_ERROR;
      break;
    }
    key_buff= info->lastkey+info->s->base.max_key_length;
    start_key_len= _mi_pack_key(info,inx, key_buff,
                                (uchar*) min_key->key, min_key->keypart_map,
                                (HA_KEYSEG**) 0);
    res= rtree_estimate(info, inx, key_buff, start_key_len,
                        myisam_read_vec[min_key->flag]);
    res= res ? res : 1;                       /* Don't return 0 */
    break;
  }
#endif
  case HA_KEY_ALG_BTREE:
  default:
    start_pos= (min_key ?  _mi_record_pos(info, min_key->key,
                                          min_key->keypart_map, min_key->flag)
                        : (ha_rows) 0);
    end_pos=   (max_key ?  _mi_record_pos(info, max_key->key,
                                          max_key->keypart_map, max_key->flag)
                        : info->state->records + (ha_rows) 1);
    res= (end_pos < start_pos ? (ha_rows) 0 :
          (end_pos == start_pos ? (ha_rows) 1 : end_pos-start_pos));
    if (start_pos == HA_POS_ERROR || end_pos == HA_POS_ERROR)
      res=HA_POS_ERROR;
  }
