switch (msg) {

    case WM_SHOWWINDOW:
        {
            if (wParam) {
                SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_SHOWN, 0, 0);
            } else {
                SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_HIDDEN, 0, 0);
            }
        }
        break;

    case WM_ACTIVATE:
        {
            BOOL minimized;

            minimized = HIWORD(wParam);
            if (!minimized && (LOWORD(wParam) != WA_INACTIVE)) {
                Uint32 mouseFlags;
                SHORT keyState;

                SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_SHOWN, 0, 0);
                SDL_SendWindowEvent(data->window,
                                    SDL_WINDOWEVENT_RESTORED, 0, 0);
                if (IsZoomed(hwnd)) {
                    SDL_SendWindowEvent(data->window,
                                        SDL_WINDOWEVENT_MAXIMIZED, 0, 0);
                }
                if (SDL_GetKeyboardFocus() != data->window) {
                    SDL_SetKeyboardFocus(data->window);
                }
                /* mouse buttons may have changed state here, we need
                to resync them, but we will get a WM_MOUSEMOVE right away which will fix
                things up if in non raw mode also
                */
                mouseFlags = SDL_GetMouseState( NULL, NULL );

                keyState = GetAsyncKeyState( VK_LBUTTON );
                WIN_CheckWParamMouseButton( ( keyState & 0x8000 ), (mouseFlags & SDL_BUTTON_LMASK), data, SDL_BUTTON_LEFT );
                keyState = GetAsyncKeyState( VK_RBUTTON );
                WIN_CheckWParamMouseButton( ( keyState & 0x8000 ), (mouseFlags & SDL_BUTTON_RMASK), data, SDL_BUTTON_RIGHT );
                keyState = GetAsyncKeyState( VK_MBUTTON );
                WIN_CheckWParamMouseButton( ( keyState & 0x8000 ), (mouseFlags & SDL_BUTTON_MMASK), data, SDL_BUTTON_MIDDLE );
                keyState = GetAsyncKeyState( VK_XBUTTON1 );
                WIN_CheckWParamMouseButton( ( keyState & 0x8000 ), (mouseFlags & SDL_BUTTON_X1MASK), data, SDL_BUTTON_X1 );
                keyState = GetAsyncKeyState( VK_XBUTTON2 );
                WIN_CheckWParamMouseButton( ( keyState & 0x8000 ), (mouseFlags & SDL_BUTTON_X2MASK), data, SDL_BUTTON_X2 );
                data->mouse_button_flags = 0;

                if(SDL_GetMouse()->relative_mode) {
                    LONG cx, cy;
                    RECT rect;
                    GetWindowRect(hwnd, &rect);

                    cx = (rect.left + rect.right) / 2;
                    cy = (rect.top + rect.bottom) / 2;

                    /* Make an absurdly small clip rect */
                    rect.left = cx-1;
                    rect.right = cx+1;
                    rect.top = cy-1;
                    rect.bottom = cy+1;

                    ClipCursor(&rect);
                }

                /*
                 * FIXME: Update keyboard state
                 */
                WIN_CheckClipboardUpdate(data->videodata);
            } else {
                if (SDL_GetKeyboardFocus() == data->window) {
                    SDL_SetKeyboardFocus(NULL);
                }
                if (minimized) {
                    SDL_SendWindowEvent(data->window,
                                        SDL_WINDOWEVENT_MINIMIZED, 0, 0);
                }
            }
        }
        returnCode = 0;
        break;

    case WM_MOUSEMOVE:
        if( !SDL_GetMouse()->relative_mode )
            SDL_SendMouseMotion(data->window, 0, 0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        /* don't break here, fall through to check the wParam like the button presses */
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP:
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_XBUTTONDOWN:
        if( !SDL_GetMouse()->relative_mode )
            WIN_CheckWParamMouseButtons( wParam, data );
        break;

    case WM_INPUT:
    {
        HRAWINPUT hRawInput = (HRAWINPUT)lParam;
        RAWINPUT inp;
        UINT size = sizeof(inp);

        if(!SDL_GetMouse()->relative_mode)
            break;

        GetRawInputData(hRawInput, RID_INPUT, &inp, &size, sizeof(RAWINPUTHEADER));

        /* Mouse data */
        if(inp.header.dwType == RIM_TYPEMOUSE)
        {
            RAWMOUSE* mouse = &inp.data.mouse;

            if((mouse->usFlags & 0x01) == MOUSE_MOVE_RELATIVE)
            {
                SDL_SendMouseMotion(data->window, 0, 1, (int)mouse->lLastX, (int)mouse->lLastY);
            }
            else
            {
                /* synthesize relative moves from the abs position */
                static SDL_Point initialMousePoint;
                if ( initialMousePoint.x == 0 && initialMousePoint.y == 0 )
                {
                    initialMousePoint.x = mouse->lLastX;
                    initialMousePoint.y = mouse->lLastY;
                }

                SDL_SendMouseMotion(data->window, 0, 1, (int)(mouse->lLastX-initialMousePoint.x), (int)(mouse->lLastY-initialMousePoint.y) );

                initialMousePoint.x = mouse->lLastX;
                initialMousePoint.y = mouse->lLastY;
            }
            WIN_CheckRawMouseButtons( mouse->usButtonFlags, data );
        }
        break;
    }

    case WM_MOUSEWHEEL:
        {
            /* FIXME: This may need to accumulate deltas up to WHEEL_DELTA */
            short motion = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;

            SDL_SendMouseWheel(data->window, 0, 0, motion);
            break;
        }

#ifdef WM_MOUSELEAVE
    case WM_MOUSELEAVE:
        if (SDL_GetMouseFocus() == data->window && !SDL_GetMouse()->relative_mode) {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(hwnd, &cursorPos);
            SDL_SendMouseMotion(data->window, 0, 0, cursorPos.x, cursorPos.y);
            SDL_SetMouseFocus(NULL);
        }
        returnCode = 0;
        break;
#endif /* WM_MOUSELEAVE */

    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
        {
            SDL_Scancode code = WindowsScanCodeToSDLScanCode( lParam, wParam );
            if ( code != SDL_SCANCODE_UNKNOWN ) {
                SDL_SendKeyboardKey(SDL_PRESSED, code );
            }
        }
        returnCode = 0;
        break;

    case WM_SYSKEYUP:
    case WM_KEYUP:
        {
            SDL_Scancode code = WindowsScanCodeToSDLScanCode( lParam, wParam );
            if ( code != SDL_SCANCODE_UNKNOWN ) {
                if (code == SDL_SCANCODE_PRINTSCREEN &&
                    SDL_GetKeyboardState(NULL)[code] == SDL_RELEASED) {
                    SDL_SendKeyboardKey(SDL_PRESSED, code);
                }
                SDL_SendKeyboardKey(SDL_RELEASED, code);
            }
        }
        returnCode = 0;
        break;

    case WM_CHAR:
        {
            char text[4];

            /* Convert to UTF-8 and send it on... */
            if (wParam <= 0x7F) {
                text[0] = (char) wParam;
                text[1] = '\0';
            } else if (wParam <= 0x7FF) {
                text[0] = 0xC0 | (char) ((wParam >> 6) & 0x1F);
                text[1] = 0x80 | (char) (wParam & 0x3F);
                text[2] = '\0';
            } else {
                text[0] = 0xE0 | (char) ((wParam >> 12) & 0x0F);
                text[1] = 0x80 | (char) ((wParam >> 6) & 0x3F);
                text[2] = 0x80 | (char) (wParam & 0x3F);
                text[3] = '\0';
            }
            SDL_SendKeyboardText(text);
        }
        returnCode = 0;
        break;

#ifdef WM_INPUTLANGCHANGE
    case WM_INPUTLANGCHANGE:
        {
            WIN_UpdateKeymap();
        }
        returnCode = 1;
        break;
#endif /* WM_INPUTLANGCHANGE */

#ifdef WM_GETMINMAXINFO
    case WM_GETMINMAXINFO:
        {
            MINMAXINFO *info;
            RECT size;
            int x, y;
            int w, h;
            int min_w, min_h;
            int max_w, max_h;
            int style;
            BOOL menu;
            BOOL constrain_max_size;

            /* If we allow resizing, let the resize happen naturally */
            if (SDL_IsShapedWindow(data->window))
                Win32_ResizeWindowShape(data->window);

            /* Get the current position of our window */
            GetWindowRect(hwnd, &size);
            x = size.left;
            y = size.top;

            /* Calculate current size of our window */
            SDL_GetWindowSize(data->window, &w, &h);
            SDL_GetWindowMinimumSize(data->window, &min_w, &min_h);
            SDL_GetWindowMaximumSize(data->window, &max_w, &max_h);

            /* Store in min_w and min_h difference between current size and minimal
               size so we don't need to call AdjustWindowRectEx twice */
            min_w -= w;
            min_h -= h;
            if (max_w && max_h) {
                max_w -= w;
                max_h -= h;
                constrain_max_size = TRUE;
            } else {
                constrain_max_size = FALSE;
            }

            size.top = 0;
            size.left = 0;
            size.bottom = h;
            size.right = w;

            style = GetWindowLong(hwnd, GWL_STYLE);
            /* DJM - according to the docs for GetMenu(), the
               return value is undefined if hwnd is a child window.
               Aparently it's too difficult for MS to check
               inside their function, so I have to do it here.
             */
            menu = (style & WS_CHILDWINDOW) ? FALSE : (GetMenu(hwnd) != NULL);
            AdjustWindowRectEx(&size, style, menu, 0);
            w = size.right - size.left;
            h = size.bottom - size.top;

            /* Fix our size to the current size */
            info = (MINMAXINFO *) lParam;
            if (SDL_GetWindowFlags(data->window) & SDL_WINDOW_RESIZABLE) {
                info->ptMinTrackSize.x = w + min_w;
                info->ptMinTrackSize.y = h + min_h;
                if (constrain_max_size) {
                    info->ptMaxTrackSize.x = w + max_w;
                    info->ptMaxTrackSize.y = h + max_h;
                }
            } else {
                info->ptMaxSize.x = w;
                info->ptMaxSize.y = h;
                info->ptMaxPosition.x = x;
                info->ptMaxPosition.y = y;
                info->ptMinTrackSize.x = w;
                info->ptMinTrackSize.y = h;
                info->ptMaxTrackSize.x = w;
                info->ptMaxTrackSize.y = h;
            }
        }
        returnCode = 0;
        break;
#endif /* WM_GETMINMAXINFO */

    case WM_WINDOWPOSCHANGED:
        {
            RECT rect;
            int x, y;
            int w, h;
            Uint32 window_flags;

            if (!GetClientRect(hwnd, &rect) ||
                (rect.right == rect.left && rect.bottom == rect.top)) {
                break;
            }
            ClientToScreen(hwnd, (LPPOINT) & rect);
            ClientToScreen(hwnd, (LPPOINT) & rect + 1);

            window_flags = SDL_GetWindowFlags(data->window);
            if ((window_flags & SDL_WINDOW_INPUT_GRABBED) &&
                (window_flags & SDL_WINDOW_INPUT_FOCUS)) {
                ClipCursor(&rect);
            }

            x = rect.left;
            y = rect.top;
            SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_MOVED, x, y);

            w = rect.right - rect.left;
            h = rect.bottom - rect.top;
            SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_RESIZED, w,
                                h);
        }
        break;

    case WM_SETCURSOR:
        {
            Uint16 hittest;

            hittest = LOWORD(lParam);
            if (hittest == HTCLIENT) {
                SetCursor(SDL_cursor);
                returnCode = TRUE;
            }
        }
        break;

        /* We were occluded, refresh our display */
    case WM_PAINT:
        {
            RECT rect;
            if (GetUpdateRect(hwnd, &rect, FALSE)) {
                ValidateRect(hwnd, NULL);
                SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_EXPOSED,
                                    0, 0);
            }
        }
        returnCode = 0;
        break;

        /* We'll do our own drawing, prevent flicker */
    case WM_ERASEBKGND:
        {
        }
        return (1);

#if defined(SC_SCREENSAVE) || defined(SC_MONITORPOWER)
    case WM_SYSCOMMAND:
        {
            /* Don't start the screensaver or blank the monitor in fullscreen apps */
            if ((wParam & 0xFFF0) == SC_SCREENSAVE ||
                (wParam & 0xFFF0) == SC_MONITORPOWER) {
                if (SDL_GetVideoDevice()->suspend_screensaver) {
                    return (0);
                }
            }
        }
        break;
#endif /* System has screensaver support */

    case WM_CLOSE:
        {
            SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_CLOSE, 0, 0);
        }
        returnCode = 0;
        break;

    case WM_TOUCH:
        {
            UINT i, num_inputs = LOWORD(wParam);
            PTOUCHINPUT inputs = SDL_stack_alloc(TOUCHINPUT, num_inputs);
            if (data->videodata->GetTouchInputInfo((HTOUCHINPUT)lParam, num_inputs, inputs, sizeof(TOUCHINPUT))) {
                RECT rect;
                float x, y;

                if (!GetClientRect(hwnd, &rect) ||
                    (rect.right == rect.left && rect.bottom == rect.top)) {
                    if (inputs) {
                        SDL_stack_free(inputs);
                    }
                    break;
                }
                ClientToScreen(hwnd, (LPPOINT) & rect);
                ClientToScreen(hwnd, (LPPOINT) & rect + 1);
                rect.top *= 100;
                rect.left *= 100;
                rect.bottom *= 100;
                rect.right *= 100;

                for (i = 0; i < num_inputs; ++i) {
                    PTOUCHINPUT input = &inputs[i];

                    const SDL_TouchID touchId = (SDL_TouchID)((size_t)input->hSource);
                    if (!SDL_GetTouch(touchId)) {
                        if (SDL_AddTouch(touchId, "") < 0) {
                            continue;
                        }
                    }

                    /* Get the normalized coordinates for the window */
                    x = (float)(input->x - rect.left)/(rect.right - rect.left);
                    y = (float)(input->y - rect.top)/(rect.bottom - rect.top);

                    if (input->dwFlags & TOUCHEVENTF_DOWN) {
                        SDL_SendTouch(touchId, input->dwID, SDL_TRUE, x, y, 1.0f);
                    }
                    if (input->dwFlags & TOUCHEVENTF_MOVE) {
                        SDL_SendTouchMotion(touchId, input->dwID, x, y, 1.0f);
                    }
                    if (input->dwFlags & TOUCHEVENTF_UP) {
                        SDL_SendTouch(touchId, input->dwID, SDL_FALSE, x, y, 1.0f);
                    }
                }
            }
            SDL_stack_free(inputs);

            data->videodata->CloseTouchInputHandle((HTOUCHINPUT)lParam);
            return 0;
        }
        break;

    case WM_DROPFILES:
        {
            UINT i;
            HDROP drop = (HDROP) wParam;
            UINT count = DragQueryFile(drop, 0xFFFFFFFF, NULL, 0);
            for (i = 0; i < count; ++i) {
                UINT size = DragQueryFile(drop, i, NULL, 0) + 1;
                LPTSTR buffer = SDL_stack_alloc(TCHAR, size);
                if (buffer) {
                    if (DragQueryFile(drop, i, buffer, size)) {
                        char *file = WIN_StringToUTF8(buffer);
                        SDL_SendDropFile(file);
                        SDL_free(file);
                    }
                    SDL_stack_free(buffer);
                }
            }
            DragFinish(drop);
            return 0;
        }
        break;
    }
