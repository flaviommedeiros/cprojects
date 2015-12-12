switch (info->s->keyinfo[inx].key_alg) {
#ifdef HAVE_RTREE_KEYS
    case HA_KEY_ALG_RTREE:
      /*
	Note that rtree doesn't support that the table
	may be changed since last call, so we do need
	to skip rows inserted by other threads like in btree
      */
      error= rtree_get_next(info,inx,info->lastkey_length);
      break;
#endif
    case HA_KEY_ALG_BTREE:
    default:
      if (!changed)
	error= _mi_search_next(info,info->s->keyinfo+inx,info->lastkey,
			       info->lastkey_length,flag,
			       info->s->state.key_root[inx]);
      else
	error= _mi_search(info,info->s->keyinfo+inx,info->lastkey,
			  USE_WHOLE_KEY,flag, info->s->state.key_root[inx]);
    }
