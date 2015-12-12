switch (theEvent.what) {
			case mouseDown:
				HandleMouseDown(&theEvent);
				if(postMessageHook) postMessageHook(&theEvent);
				return false;
			break;

			case mouseUp:
			    gButtonIsDown = false;
				if(inputSemaphoreIndex) {
					recordMouseEvent(&theEvent,MouseModifierState(&theEvent));
    				if(postMessageHook) postMessageHook(&theEvent);
					return false;
				}
				recordModifierButtons(&theEvent);
				if(postMessageHook) postMessageHook(&theEvent);
				return false;
			break;

			case keyDown:
			case autoKey:
                if ((theEvent.modifiers & cmdKey) != 0) {
					AdjustMenus();
					isMenuKey = MenuKey(theEvent.message & charCodeMask);
					if (isMenuKey) {
						HandleMenu(isMenuKey);
						break;
					}
				}
				if(inputSemaphoreIndex) {
					recordKeyboardEvent(&theEvent,EventKeyDown);
					break;
				}
				recordModifierButtons(&theEvent);
				recordKeystroke(&theEvent);
			break;
			
			case keyUp:
				if(inputSemaphoreIndex) {
					recordKeyboardEvent(&theEvent,EventKeyUp);
				}
			break;

#ifndef IHAVENOHEAD
			case updateEvt:
				 {
				WindowPtr window = (WindowPtr) theEvent.message;

				RgnHandle updateRgn = NewRgn();
				Rect structureRect;
				
				BeginUpdate(window);
				GetPortVisibleRegion((CGrafPtr)window,updateRgn);
				GetRegionBounds(updateRgn,&structureRect);
				DisposeRgn(updateRgn);
				if (windowIndexFromHandle(window))
					recordWindowEvent(WindowEventPaint,structureRect.left, structureRect.top, structureRect.right, structureRect.bottom);
				if (windowIndexFromHandle(window) == 1) fullDisplayUpdate();  /* this makes VM call ioShowDisplay */					
				EndUpdate(window);
				}
			break;

			case activateEvt:
				if (theEvent.modifiers & activeFlag && ((windowIndexFromHandle((WindowPtr) theEvent.message)))) {
					windowActive = (windowIndexFromHandle((WindowPtr) theEvent.message));
					recordWindowEvent(WindowEventActivated,0, 0, 0, 0);
				} else {
					GetMouse(&savedMousePosition);
					windowActive = 0;
				}
				fullDisplayUpdate();  /* Fix for full screen menu bar tabbing*/
			break;
#endif

			case kHighLevelEvent:
				AEProcessAppleEvent(&theEvent);
			break;
			
			case osEvt: 
				if (((theEvent.message>>24)& 0xFF) == suspendResumeMessage) {
				
					//JMM July 4th 2000
					//Fix for menu bar tabbing, thanks to Javier Diaz-Reinoso for pointing this out
					//
					if ((theEvent.message & resumeFlag) == 0) {
						GetMouse(&savedMousePosition);
						windowActive = 0;
						if (getFullScreenFlag())
							MenuBarRestore();
					} else {
 						windowActive = (windowIndexFromHandle((WindowPtr) FrontWindow()));
 						if (getFullScreenFlag()) {
							MenuBarHide();
            				fullDisplayUpdate();  /* Fix for full screen menu bar tabbing*/
						}
					}
				}
				break;
		}
