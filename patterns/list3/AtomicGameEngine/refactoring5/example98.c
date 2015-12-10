#ifdef __MMX__
if (SDL_HasMMX())
                            return Blit555to555SurfaceAlphaMMX;
                        else
#endif
                            return Blit555to555SurfaceAlpha;
