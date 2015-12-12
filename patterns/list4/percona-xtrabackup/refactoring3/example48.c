switch(info->s->keyinfo[inx].key_alg){
#ifdef HAVE_RTREE_KEYS
    case HA_KEY_ALG_RTREE:
      error=rtree_get_first(info,inx,info->lastkey_length);
      break;
#endif
    case HA_KEY_ALG_BTREE:
    default:
      error=_mi_search_first(info,info->s->keyinfo+inx,
			   info->s->state.key_root[inx]);
      break;
    }
