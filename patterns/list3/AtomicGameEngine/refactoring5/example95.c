#ifdef USE_DYNAMIC_TEXTURE
if (texture->access == SDL_TEXTUREACCESS_STREAMING) {
        pool = D3DPOOL_DEFAULT;
        usage = D3DUSAGE_DYNAMIC;
    } else
#endif
    if (texture->access == SDL_TEXTUREACCESS_TARGET) {
        /* D3DPOOL_MANAGED does not work with D3DUSAGE_RENDERTARGET */
        pool = D3DPOOL_DEFAULT;
        usage = D3DUSAGE_RENDERTARGET;
    } else {
        pool = D3DPOOL_MANAGED;
        usage = 0;
    }
