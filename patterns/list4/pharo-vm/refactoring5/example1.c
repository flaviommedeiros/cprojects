#ifndef NO_PLUGIN_SUPPORT
if(msg.hwnd == NULL) {
	pluginHandleEvent(&msg);
      } else
#endif
	if(msg.hwnd != stWindow) {
	  /* Messages not sent to Squeak window */
	  if(msg.hwnd != consoleWindow && GetParent(msg.hwnd) == stWindow) {
	    /* This message has been sent to a plugin window */
	    /* Selectively pass up certain events to the parent's level */
	    switch (msg.message) {
	      case WM_LBUTTONDOWN:
	      case WM_LBUTTONUP:
	      case WM_MBUTTONDOWN:
	      case WM_MBUTTONUP:
	      case WM_RBUTTONDOWN:
	      case WM_RBUTTONUP:
	      case WM_MOUSEMOVE:
		mousePt.x = LOWORD(msg.lParam);
		mousePt.y = HIWORD(msg.lParam);
		MapWindowPoints(msg.hwnd, stWindow, &mousePt, 1);
		PostMessage(stWindow, msg.message, msg.wParam, MAKELONG(mousePt.x,mousePt.y));
	    }
	  }
	}
