switch (ev->window.event) {
#ifdef TCOD_ANDROID
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			{
				/* printf("SDL2 WINDOWEVENT (SDL_WINDOWEVENT_SIZE_CHANGED): 0x%04x w=%d h=%d\n", ev->window.event, ev->window.data1, ev->window.data2); */
				/* If the app is started while the device is locked, the screen will be in portrait mode.  We need to rescale when it changes. */
				if (scale_data.surface_width != ev->window.data1 || scale_data.surface_height != ev->window.data1)
					scale_data.force_recalc = 1;
				break;
			}
#endif
			case SDL_WINDOWEVENT_ENTER:          /**< Window has gained mouse focus */
				TCOD_ctx.app_has_mouse_focus=true; break;
			case SDL_WINDOWEVENT_LEAVE:          /**< Window has lost mouse focus */
				TCOD_ctx.app_has_mouse_focus=false; break;
			case SDL_WINDOWEVENT_MAXIMIZED:      /**< Window has been maximized */
				TCOD_ctx.app_is_active=true; break;
			case SDL_WINDOWEVENT_MINIMIZED:      /**< Window has been minimized */
				TCOD_ctx.app_is_active=false; break;
#ifdef NDEBUG_HMM
			default:
				TCOD_LOG(("SDL2 WINDOWEVENT (unknown): 0x%04x\n", ev->window.event));
				break;
#endif
			}
