REBFRM *Make_Frame_Detect(
    enum Reb_Kind kind,
    REBFRM *spec,
    REBARR *body,
    REBVAL value[],
    REBFRM *opt_parent
) {
    REBARR *keylist;
    REBFRM *frame;

#if !defined(NDEBUG)
    PG_Reb_Stats->Objects++;
#endif

    if (IS_END(value)) {
        if (opt_parent) {
            frame = AS_FRAME(Copy_Array_Core_Managed(
                FRAME_VARLIST(opt_parent),
                0, // at
                FRAME_LEN(opt_parent) + 1, // tail (+1 for context/rootkey)
                0, // extra
                TRUE, // deep
                TS_CLONE // types
            ));
            ARRAY_SET_FLAG(FRAME_VARLIST(frame), SER_FRAME);
            FRAME_KEYLIST(frame) = FRAME_KEYLIST(opt_parent);
            VAL_FRAME(FRAME_CONTEXT(frame)) = frame;
        }
        else {
            frame = Alloc_Frame(0, TRUE);
            MANAGE_FRAME(frame);
        }
    }
    else {
        keylist = Collect_Frame(opt_parent, &value[0], BIND_ONLY); // GC safe
        frame = Create_Frame(keylist, NULL); // GC safe
        if (opt_parent) {
            if (Reb_Opts->watch_obj_copy)
                Debug_Fmt(
                    cs_cast(BOOT_STR(RS_WATCH, 2)),
                    FRAME_LEN(opt_parent),
                    FRAME_KEYLIST(frame)
                );

            // Bitwise copy parent values (will have bits fixed by Clonify)
            memcpy(
                FRAME_VARS_HEAD(frame),
                FRAME_VARS_HEAD(opt_parent),
                (FRAME_LEN(opt_parent)) * sizeof(REBVAL)
            );

            // For values we copied that were blocks and strings, replace
            // their series components with deep copies of themselves:
            Clonify_Values_Len_Managed(
                FRAME_VAR(frame, 1), FRAME_LEN(frame), TRUE, TS_CLONE
            );

            // The *word series* might have been reused from the parent,
            // based on whether any words were added, or we could have gotten
            // a fresh one back.  Force our invariant here (as the screws
            // tighten...)
            ENSURE_ARRAY_MANAGED(FRAME_KEYLIST(frame));
            MANAGE_ARRAY(FRAME_VARLIST(frame));
        }
        else {
            MANAGE_FRAME(frame);
        }

        assert(keylist == FRAME_KEYLIST(frame));
    }

    VAL_RESET_HEADER(FRAME_CONTEXT(frame), kind);
    assert(FRAME_TYPE(frame) == kind);

    FRAME_SPEC(frame) = spec;
    FRAME_BODY(frame) = body;

    ASSERT_ARRAY_MANAGED(FRAME_VARLIST(frame));
    ASSERT_ARRAY_MANAGED(FRAME_KEYLIST(frame));
    ASSERT_FRAME(frame);

    return frame;
}
