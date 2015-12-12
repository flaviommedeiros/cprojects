#ifdef DEPRECATED_GDK_KEYSYMS
if (keyval != GDK_VoidSymbol)
#else
    if (keyval != GDK_KEY_VoidSymbol)
#endif
        c = gdk_keyval_to_unicode(keyval);
