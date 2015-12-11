#ifdef __MMX__
if (SDL_HasMMX())
                            return Blit565to565SurfaceAlphaMMX;
                        else
#endif
                            return Blit565to565SurfaceAlpha;
