switch (msg) {
#ifdef WM_ACTIVATEAPP
		case WM_ACTIVATEAPP: {
			int i, active;

			active = (wParam && (GetForegroundWindow() == hwnd));
			if ( active ) {
				for ( i=0; SDL_DIdev[i]; ++i ) {
					IDirectInputDevice2_Acquire(
								SDL_DIdev[i]);
				}
			} else {
				for ( i=0; SDL_DIdev[i]; ++i ) {
					IDirectInputDevice2_Unacquire(
								SDL_DIdev[i]);
				}
				mouse_lost = 1;
			}
		}
		break;
#endif /* WM_ACTIVATEAPP */

#ifdef WM_DISPLAYCHANGE
		case WM_DISPLAYCHANGE: {
			WPARAM BitsPerPixel;
			WORD SizeX, SizeY;

			/* Ack!  The display changed size and/or depth! */
			SizeX = LOWORD(lParam);
			SizeY = HIWORD(lParam);
			BitsPerPixel = wParam;
			/* We cause this message when we go fullscreen */
		}
		break;
#endif /* WM_DISPLAYCHANGE */

		/* The keyboard is handled via DirectInput */
		case WM_SYSKEYUP:
		case WM_SYSKEYDOWN: {
			/* Pass syskey to DefWindwoProc (ALT-F4, etc.) */
		}
		break;
		case WM_KEYUP:
		case WM_KEYDOWN: {
			/* Ignore windows keyboard messages */;
		}
		return(0);

#if defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
		/* Don't allow screen savers or monitor power downs.
		   This is because they quietly clear DirectX surfaces.
		   It would be better to allow the application to
		   decide whether or not to blow these off, but the
		   semantics of SDL_PrivateSysWMEvent() don't allow
		   the application that choice.
		 */
		case WM_SYSCOMMAND: {
			if ((wParam&0xFFF0)==SC_SCREENSAVE || 
			    (wParam&0xFFF0)==SC_MONITORPOWER)
				return(0);
		}
		/* Fall through to default processing */

#endif /* SC_SCREENSAVE || SC_MONITORPOWER */

		default: {
			/* Only post the event if we're watching for it */
			if ( SDL_ProcessEvents[SDL_SYSWMEVENT] == SDL_ENABLE ) {
			        SDL_SysWMmsg wmmsg;

				SDL_VERSION(&wmmsg.version);
				wmmsg.hwnd = hwnd;
				wmmsg.msg = msg;
				wmmsg.wParam = wParam;
				wmmsg.lParam = lParam;
				posted = SDL_PrivateSysWMEvent(&wmmsg);

			/* DJM: If the user isn't watching for private
				messages in her SDL event loop, then pass it
				along to any win32 specific window proc.
			 */
			} else if (userWindowProc) {
				return CallWindowProc(userWindowProc, hwnd, msg, wParam, lParam);
			}
		}
		break;
	}
