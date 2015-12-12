if (old_artwork_enable_embedded != artwork_enable_embedded ||
        old_artwork_enable_local != artwork_enable_local ||
#ifdef USE_VFS_CURL
        old_artwork_enable_lfm != artwork_enable_lfm ||
        old_artwork_enable_mb != artwork_enable_mb ||
        old_artwork_enable_aao != artwork_enable_aao ||
        old_artwork_enable_wos != artwork_enable_wos ||
#endif
        old_artwork_filemask != artwork_filemask) {
        trace ("artwork config changed, invalidating cache...\n");
        deadbeef->mutex_lock (queue_mutex);
        insert_cache_reset (&cache_reset_time);
        artwork_abort_http_request ();
        deadbeef->mutex_unlock (queue_mutex);
    }
    else if (old_scale_towards_longer != scale_towards_longer) {
        trace ("artwork config changed, invalidating scaled cache...\n");
        deadbeef->mutex_lock (queue_mutex);
        insert_cache_reset (&scaled_cache_reset_time);
        deadbeef->mutex_unlock (queue_mutex);
    }
