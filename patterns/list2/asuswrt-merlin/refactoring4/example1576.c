#ifdef MAP_ANONYMOUS
if (c->lumMmx2FilterCode == MAP_FAILED || c->chrMmx2FilterCode == MAP_FAILED)
#else
            if (!c->lumMmx2FilterCode || !c->chrMmx2FilterCode)
#endif
                return AVERROR(ENOMEM);
