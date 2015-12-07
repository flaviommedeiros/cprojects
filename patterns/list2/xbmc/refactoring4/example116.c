#if COMPILE_TEMPLATE_MMX
if (c->flags & SWS_FAST_BILINEAR && c->canMMX2BeUsed)
#else
    if (c->flags & SWS_FAST_BILINEAR)
#endif
    {
        c->hyscale_fast = RENAME(hyscale_fast);
        c->hcscale_fast = RENAME(hcscale_fast);
    }
