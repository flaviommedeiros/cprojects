static uint8_t *udict_inline_find(struct udict *udict, const char *name,
                                  enum udict_type type)
{
    struct udict_inline *inl = udict_inline_from_udict(udict);
#ifdef STATS
    if (type > UDICT_TYPE_SHORTHAND) {
        struct udict_inline_mgr *inline_mgr =
            udict_inline_mgr_from_udict_mgr(udict->mgr);
        inline_mgr->stats[type - UDICT_TYPE_SHORTHAND - 1]++;
    }
#endif
    uint8_t *attr = umem_buffer(&inl->umem);
    while (attr != NULL) {
        if (*attr == type &&
             (type > UDICT_TYPE_SHORTHAND || type == UDICT_TYPE_END ||
              !strcmp((const char *)(attr + 3), name)))
            return attr;
        attr = udict_inline_next(attr);
    }
    return NULL;
}
