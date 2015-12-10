#ifndef TEST_SLOW_BLIT
if (blit == NULL)
#endif
    {
        Uint32 src_format = surface->format->format;
        Uint32 dst_format = dst->format->format;

        if (!SDL_ISPIXELFORMAT_INDEXED(src_format) &&
            !SDL_ISPIXELFORMAT_FOURCC(src_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(dst_format) &&
            !SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
            blit = SDL_Blit_Slow;
        }
    }
