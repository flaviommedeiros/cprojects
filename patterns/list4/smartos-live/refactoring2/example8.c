#if JS_HAS_SCRIPT_OBJECT
if (argc < 2)
#endif
    {
        /* Execute using caller's new scope object (might be a Call object). */
        if (caller)
            scopeobj = caller->scopeChain;
    }
