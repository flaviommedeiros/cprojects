if (bd->title_type == title_hdmv) {
        result = _run_gc(bd, GC_CTRL_VK_KEY, key);
#ifdef USING_BDJAVA
    } else if (bd->title_type == title_bdj) {
        result = _bdj_event(bd, BDJ_EVENT_VK_KEY, key);
#endif
    }
#endif
