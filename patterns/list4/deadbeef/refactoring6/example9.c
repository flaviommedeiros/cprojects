if (n && (processorder == 0xFFFF ? sigrenderer->order > sigrenderer->processorder : sigrenderer->order >= sigrenderer->processorder)
#ifdef BIT_ARRAY_BULLSHIT
					&& bit_array_test(sigrenderer->played, sigrenderer->processorder * 256 + sigrenderer->processrow)
#endif
					) {
#ifdef BIT_ARRAY_BULLSHIT
					sigrenderer->looped = 1;
#endif
					if (sigrenderer->callbacks->loop) {
						if ((*sigrenderer->callbacks->loop)(sigrenderer->callbacks->loop_data))
							return 1;
#ifdef BIT_ARRAY_BULLSHIT
						bit_array_reset(sigrenderer->played);
#endif
						if (sigrenderer->speed == 0)
							goto speed0; /* I love goto */
					}
				}
