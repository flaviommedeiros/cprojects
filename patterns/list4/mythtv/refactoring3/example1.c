switch (idx) {
        case BLURAY_PLAYER_SETTING_AUDIO_LANG:
        case BLURAY_PLAYER_SETTING_PG_LANG:
        case BLURAY_PLAYER_SETTING_MENU_LANG:
            return bd_set_player_setting(bd, idx, str_to_uint32(s, 3));

        case BLURAY_PLAYER_SETTING_COUNTRY_CODE:
            return bd_set_player_setting(bd, idx, str_to_uint32(s, 2));

#ifdef USING_BDJAVA
        case BLURAY_PLAYER_CACHE_ROOT:
        case BLURAY_PLAYER_PERSISTENT_ROOT:
            switch (idx) {
                case BLURAY_PLAYER_CACHE_ROOT:
                    bd_mutex_lock(&bd->mutex);
                    X_FREE(bd->bdjstorage.cache_root);
                    bd->bdjstorage.cache_root = str_dup(s);
                    bd_mutex_unlock(&bd->mutex);
                    BD_DEBUG(DBG_BDJ, "Cache root dir set to %s\n", bd->bdjstorage.cache_root);
                    return 1;

                case BLURAY_PLAYER_PERSISTENT_ROOT:
                    bd_mutex_lock(&bd->mutex);
                    X_FREE(bd->bdjstorage.persistent_root);
                    bd->bdjstorage.persistent_root = str_dup(s);
                    bd_mutex_unlock(&bd->mutex);
                    BD_DEBUG(DBG_BDJ, "Persistent root dir set to %s\n", bd->bdjstorage.persistent_root);
                    return 1;
            }
#endif /* USING_BDJAVA */
        default:
            return 0;
    }
