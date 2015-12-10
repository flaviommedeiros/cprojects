switch (msg) {

		case WM_ACTIVATE: {
			SDL_VideoDevice *this = current_video;
			BOOL active, minimized;
			Uint8 appstate;

			minimized = HIWORD(wParam);
			active = (LOWORD(wParam) != WA_INACTIVE) && !minimized;
			if ( active ) {
				/* Gain the following states */
				appstate = SDL_APPACTIVE|SDL_APPINPUTFOCUS;
				if ( this->input_grab != SDL_GRAB_OFF ) {
					WIN_GrabInput(this, SDL_GRAB_ON);
				}
				if ( !(SDL_GetAppState()&SDL_APPINPUTFOCUS) ) {
					if ( ! DDRAW_FULLSCREEN() ) {
						DIB_SwapGamma(this);
					}
					if ( WINDIB_FULLSCREEN() ) {
						SDL_RestoreGameMode();
					}
				}
#if defined(_WIN32_WCE)
				if ( WINDIB_FULLSCREEN() ) {
					LoadAygshell();
					if( SHFullScreen )
						SHFullScreen(SDL_Window, SHFS_HIDESTARTICON|SHFS_HIDETASKBAR|SHFS_HIDESIPBUTTON);
					else
						ShowWindow(FindWindow(TEXT("HHTaskBar"),NULL),SW_HIDE);
				}
#endif
				posted = SDL_PrivateAppActive(1, appstate);
				WIN_GetKeyboardState();
			} else {
				/* Lose the following states */
				appstate = SDL_APPINPUTFOCUS;
				if ( minimized ) {
					appstate |= SDL_APPACTIVE;
				}
				if ( this->input_grab != SDL_GRAB_OFF ) {
					WIN_GrabInput(this, SDL_GRAB_OFF);
				}
				if ( SDL_GetAppState() & SDL_APPINPUTFOCUS ) {
					if ( ! DDRAW_FULLSCREEN() ) {
						DIB_SwapGamma(this);
					}
					if ( WINDIB_FULLSCREEN() ) {
						SDL_RestoreDesktopMode();
#if defined(_WIN32_WCE)
						LoadAygshell();
						if( SHFullScreen ) 
							SHFullScreen(SDL_Window, SHFS_SHOWSTARTICON|SHFS_SHOWTASKBAR|SHFS_SHOWSIPBUTTON);
						else
							ShowWindow(FindWindow(TEXT("HHTaskBar"),NULL),SW_SHOW);
#endif
					}
				}
				posted = SDL_PrivateAppActive(0, appstate);
			}
			WIN_Activate(this, active, minimized);
			return(0);
		}
		break;

		case WM_MOUSEMOVE: {
			
			/* Mouse is handled by DirectInput when fullscreen */
			if ( SDL_VideoSurface && ! DINPUT_FULLSCREEN() ) {
				Sint16 x, y;

				/* mouse has entered the window */
				if ( ! in_window ) {
#ifdef WM_MOUSELEAVE
					TRACKMOUSEEVENT tme;

					tme.cbSize = sizeof(tme);
					tme.dwFlags = TME_LEAVE;
					tme.hwndTrack = SDL_Window;
					_TrackMouseEvent(&tme);
#endif /* WM_MOUSELEAVE */
					in_window = TRUE;

					posted = SDL_PrivateAppActive(1, SDL_APPMOUSEFOCUS);
				}

				/* mouse has moved within the window */
				x = LOWORD(lParam);
				y = HIWORD(lParam);
				if ( mouse_relative ) {
					POINT center;
					center.x = (SDL_VideoSurface->w/2);
					center.y = (SDL_VideoSurface->h/2);
					x -= (Sint16)center.x;
					y -= (Sint16)center.y;
					if ( x || y ) {
						ClientToScreen(SDL_Window, &center);
						SetCursorPos(center.x, center.y);
						posted = SDL_PrivateMouseMotion(0, 1, x, y);
					}
				} else {
#ifdef _WIN32_WCE
					if (SDL_VideoSurface)
						GapiTransform(this->hidden->userOrientation, this->hidden->hiresFix, &x, &y);
#endif
					posted = SDL_PrivateMouseMotion(0, 0, x, y);
				}
			}
		}
		return(0);

#ifdef WM_MOUSELEAVE
		case WM_MOUSELEAVE: {

			/* Mouse is handled by DirectInput when fullscreen */
			if ( SDL_VideoSurface && ! DINPUT_FULLSCREEN() ) {
				/* mouse has left the window */
				/* or */
				/* Elvis has left the building! */
				posted = SDL_PrivateAppActive(0, SDL_APPMOUSEFOCUS);
			}
			in_window = FALSE;
		}
		return(0);
#endif /* WM_MOUSELEAVE */

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP: {
			/* Mouse is handled by DirectInput when fullscreen */
			if ( SDL_VideoSurface && ! DINPUT_FULLSCREEN() ) {
				WORD xbuttonval = 0;
				Sint16 x, y;
				Uint8 button, state;

				/* DJM:
				   We want the SDL window to take focus so that
				   it acts like a normal windows "component"
				   (e.g. gains keyboard focus on a mouse click).
				 */
				SetFocus(SDL_Window);

				/* Figure out which button to use */
				switch (msg) {
					case WM_LBUTTONDOWN:
						button = SDL_BUTTON_LEFT;
						state = SDL_PRESSED;
						break;
					case WM_LBUTTONUP:
						button = SDL_BUTTON_LEFT;
						state = SDL_RELEASED;
						break;
					case WM_MBUTTONDOWN:
						button = SDL_BUTTON_MIDDLE;
						state = SDL_PRESSED;
						break;
					case WM_MBUTTONUP:
						button = SDL_BUTTON_MIDDLE;
						state = SDL_RELEASED;
						break;
					case WM_RBUTTONDOWN:
						button = SDL_BUTTON_RIGHT;
						state = SDL_PRESSED;
						break;
					case WM_RBUTTONUP:
						button = SDL_BUTTON_RIGHT;
						state = SDL_RELEASED;
						break;
					case WM_XBUTTONDOWN:
						xbuttonval = GET_XBUTTON_WPARAM(wParam);
						button = SDL_BUTTON_WHEELDOWN + xbuttonval;
						state = SDL_PRESSED;
						break;
					case WM_XBUTTONUP:
						xbuttonval = GET_XBUTTON_WPARAM(wParam);
						button = SDL_BUTTON_WHEELDOWN + xbuttonval;
						state = SDL_RELEASED;
						break;
					default:
						/* Eh? Unknown button? */
						return(0);
				}
				if ( state == SDL_PRESSED ) {
					/* Grab mouse so we get up events */
					if ( ++mouse_pressed > 0 ) {
						SetCapture(hwnd);
					}
				} else {
					/* Release mouse after all up events */
					if ( --mouse_pressed <= 0 ) {
						ReleaseCapture();
						mouse_pressed = 0;
					}
				}
				if ( mouse_relative ) {
				/*	RJR: March 28, 2000
					report internal mouse position if in relative mode */
					x = 0; y = 0;
				} else {
					x = (Sint16)LOWORD(lParam);
					y = (Sint16)HIWORD(lParam);
#ifdef _WIN32_WCE
					if (SDL_VideoSurface)
						GapiTransform(this->hidden->userOrientation, this->hidden->hiresFix, &x, &y);
#endif
				}
				posted = SDL_PrivateMouseButton(
							state, button, x, y);

				/*
				 * MSDN says:
				 *  "Unlike the WM_LBUTTONUP, WM_MBUTTONUP, and WM_RBUTTONUP
				 *   messages, an application should return TRUE from [an 
				 *   XBUTTON message] if it processes it. Doing so will allow
				 *   software that simulates this message on Microsoft Windows
				 *   systems earlier than Windows 2000 to determine whether
				 *   the window procedure processed the message or called
				 *   DefWindowProc to process it.
				 */
				if (xbuttonval > 0)
					return(TRUE);
			}
		}
		return(0);


#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		case WM_MOUSEWHEEL: 
			if ( SDL_VideoSurface && ! DINPUT_FULLSCREEN() ) {
				int move = (short)HIWORD(wParam);
				if ( move ) {
					Uint8 button;
					if ( move > 0 )
						button = SDL_BUTTON_WHEELUP;
					else
						button = SDL_BUTTON_WHEELDOWN;
					posted = SDL_PrivateMouseButton(
						SDL_PRESSED, button, 0, 0);
					posted |= SDL_PrivateMouseButton(
						SDL_RELEASED, button, 0, 0);
				}
			}
			return(0);
#endif

#ifdef WM_GETMINMAXINFO
		/* This message is sent as a way for us to "check" the values
		 * of a position change.  If we don't like it, we can adjust
		 * the values before they are changed.
		 */
		case WM_GETMINMAXINFO: {
			MINMAXINFO *info;
			RECT        size;
			int x, y;
			int style;
			int width;
			int height;

			/* We don't want to clobber an internal resize */
			if ( SDL_resizing )
				return(0);

			/* We allow resizing with the SDL_RESIZABLE flag */
			if ( SDL_PublicSurface &&
				(SDL_PublicSurface->flags & SDL_RESIZABLE) ) {
				return(0);
			}

			/* Get the current position of our window */
			GetWindowRect(SDL_Window, &size);
			x = size.left;
			y = size.top;

			/* Calculate current width and height of our window */
			size.top = 0;
			size.left = 0;
			if ( SDL_PublicSurface != NULL ) {
				size.bottom = SDL_PublicSurface->h;
				size.right = SDL_PublicSurface->w;
			} else {
				size.bottom = 0;
				size.right = 0;
			}

			/* DJM - according to the docs for GetMenu(), the
			   return value is undefined if hwnd is a child window.
			   Aparently it's too difficult for MS to check
			   inside their function, so I have to do it here.
          		 */
         		style = GetWindowLong(hwnd, GWL_STYLE);
         		AdjustWindowRect(
				&size,
				style,
            			style & WS_CHILDWINDOW ? FALSE
						       : GetMenu(hwnd) != NULL);

			width = size.right - size.left;
			height = size.bottom - size.top;

			/* Fix our size to the current size */
			info = (MINMAXINFO *)lParam;
			info->ptMaxSize.x = width;
			info->ptMaxSize.y = height;
			info->ptMaxPosition.x = x;
			info->ptMaxPosition.y = y;
			info->ptMinTrackSize.x = width;
			info->ptMinTrackSize.y = height;
			info->ptMaxTrackSize.x = width;
			info->ptMaxTrackSize.y = height;
		}
		return(0);
#endif /* WM_GETMINMAXINFO */

		case WM_WINDOWPOSCHANGED: {
			SDL_VideoDevice *this = current_video;
			int w, h;

			GetClientRect(SDL_Window, &SDL_bounds);
			ClientToScreen(SDL_Window, (LPPOINT)&SDL_bounds);
			ClientToScreen(SDL_Window, (LPPOINT)&SDL_bounds+1);
			if ( !SDL_resizing && !IsZoomed(SDL_Window) &&
			     SDL_PublicSurface &&
				!(SDL_PublicSurface->flags & SDL_FULLSCREEN) ) {
				SDL_windowX = SDL_bounds.left;
				SDL_windowY = SDL_bounds.top;
			}
			w = SDL_bounds.right-SDL_bounds.left;
			h = SDL_bounds.bottom-SDL_bounds.top;
			if ( this->input_grab != SDL_GRAB_OFF ) {
				ClipCursor(&SDL_bounds);
			}
			if ( SDL_PublicSurface && 
				(SDL_PublicSurface->flags & SDL_RESIZABLE) ) {
				SDL_PrivateResize(w, h);
			}
		}
		break;

		/* We need to set the cursor */
		case WM_SETCURSOR: {
			Uint16 hittest;

			hittest = LOWORD(lParam);
			if ( hittest == HTCLIENT ) {
				SetCursor(SDL_hcursor);
				return(TRUE);
			}
		}
		break;

		/* We are about to get palette focus! */
		case WM_QUERYNEWPALETTE: {
			WIN_RealizePalette(current_video);
			return(TRUE);
		}
		break;

		/* Another application changed the palette */
		case WM_PALETTECHANGED: {
			WIN_PaletteChanged(current_video, (HWND)wParam);
		}
		break;

		/* We were occluded, refresh our display */
		case WM_PAINT: {
			HDC hdc;
			PAINTSTRUCT ps;

			hdc = BeginPaint(SDL_Window, &ps);
			if ( current_video->screen &&
			     !(current_video->screen->flags & SDL_OPENGL) ) {
				WIN_WinPAINT(current_video, hdc);
			}
			EndPaint(SDL_Window, &ps);
		}
		return(0);

		/* DJM: Send an expose event in this case */
		case WM_ERASEBKGND: {
			posted = SDL_PrivateExpose();
		}
		return(0);

		case WM_CLOSE: {
			if ( (posted = SDL_PrivateQuit()) )
				PostQuitMessage(0);
		}
		return(0);

		case WM_DESTROY: {
			PostQuitMessage(0);
		}
		return(0);

#ifndef NO_GETKEYBOARDSTATE
		case WM_INPUTLANGCHANGE: {
			codepage = GetCodePage();
		}
		return(TRUE);
#endif

		default: {
			/* Special handling by the video driver */
			if (HandleMessage) {
				return(HandleMessage(current_video,
			                     hwnd, msg, wParam, lParam));
			}
		}
		break;
	}
