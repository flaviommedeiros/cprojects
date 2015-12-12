switch (windowCode) {
		case inSysWindow:
#if !TARGET_API_MAC_CARBON
			SystemClick(theEvent, theWindow);
#endif
		break;

		case inMenuBar:
			AdjustMenus();
			isMenuKey = MenuSelect(theEvent->where);
			if (isMenuKey) {
				HandleMenu(isMenuKey);
			}
		break;

#ifndef IHAVENOHEAD
		case inDrag:
			if (getFullScreenFlag()) 	
				break;
				
			GetRegionBounds(GetGrayRgn(), &dragBounds);
			DragWindow( theWindow, theEvent->where, &dragBounds);
			GetWindowContentRgn (theWindow, ioWinRgn);
			GetRegionBounds(ioWinRgn,&globalBounds);
			recordWindowEvent(WindowEventMetricChange,globalBounds.left, globalBounds.top, globalBounds.right, globalBounds.bottom);
		break;

		case inGrow:
			if (getFullScreenFlag()) 	
				break;
				
			newSize = GrowWindow(theWindow, theEvent->where, &growLimits);
				if (newSize != 0) {
				SizeWindow( theWindow, LoWord(newSize), HiWord(newSize), true);
				GetWindowContentRgn (theWindow, ioWinRgn);
				GetRegionBounds(ioWinRgn,&globalBounds);
				recordWindowEvent(WindowEventMetricChange,globalBounds.left, globalBounds.top, globalBounds.right, globalBounds.bottom);
			}
		break;

		case inZoomIn:
		case inZoomOut:
			if (getFullScreenFlag()) 	
				break;
				
			DoZoomWindow(theEvent, theWindow, windowCode,10000, 10000);
			GetWindowContentRgn (theWindow, ioWinRgn);
			GetRegionBounds(ioWinRgn,&globalBounds);
			recordWindowEvent(WindowEventMetricChange,globalBounds.left, globalBounds.top, globalBounds.right, globalBounds.bottom);
		break;

		case inContent:
			gButtonIsDown = true;
			if (theWindow == windowHandleFromIndex(windowActive)) {
				if(inputSemaphoreIndex) {
					recordMouseEvent(theEvent,MouseModifierState(theEvent));
					break;
				}
				recordMouseDown(theEvent);
			} else {
				SelectWindow(theWindow);
			}
		break;

		case inCollapseBox:
			recordWindowEvent(WindowEventIconise,0, 0, 0, 0);
		break;
		
		case inGoAway:
			recordWindowEvent(WindowEventClose,0, 0, 0, 0);
		break;
#endif
	}
