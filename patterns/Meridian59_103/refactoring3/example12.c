switch (action)
   {
   case A_TABFWD:
      MainTab((int) action_data, True);
      break;
   case A_TABBACK:
      MainTab((int) action_data, False);
      break;

/*   case A_FORWARD:
   case A_BACKWARD:
   case A_SLIDELEFT:
   case A_SLIDERIGHT:
   case A_FORWARDFAST:
   case A_BACKWARDFAST:
      UserMovePlayer(action);
      break;

   case A_TURNLEFT:
   case A_TURNRIGHT:
   case A_TURNFASTLEFT:
   case A_TURNFASTRIGHT:
      UserTurnPlayer(action);
      break;

   case A_FORWARDTURNLEFT:
      UserMovePlayer(A_FORWARD);
      UserTurnPlayer(A_TURNLEFT);
      break;
   case A_FORWARDTURNRIGHT:
      UserMovePlayer(A_FORWARD);
      UserTurnPlayer(A_TURNRIGHT);
      break;
   case A_BACKWARDTURNLEFT:
      UserMovePlayer(A_BACKWARD);
      UserTurnPlayer(A_TURNLEFT);
      break;
   case A_BACKWARDTURNRIGHT:
      UserMovePlayer(A_BACKWARD);
      UserTurnPlayer(A_TURNRIGHT);
      break;
   case A_FORWARDTURNFASTLEFT:
      UserMovePlayer(A_FORWARD);
      UserTurnPlayer(A_TURNFASTLEFT);
      break;
   case A_FORWARDTURNFASTRIGHT:
      UserMovePlayer(A_FORWARD);
      UserTurnPlayer(A_TURNFASTRIGHT);
      break;
   case A_BACKWARDTURNFASTLEFT:
      UserMovePlayer(A_BACKWARD);
      UserTurnPlayer(A_TURNFASTLEFT);
      break;
   case A_BACKWARDTURNFASTRIGHT:
      UserMovePlayer(A_BACKWARD);
      UserTurnPlayer(A_TURNFASTRIGHT);
      break;*/

   case A_ATTACK:
      if ((GetPlayerInfo()->viewID == 0) || (GetPlayerInfo()->viewID == GetPlayerInfo()->id))
	 UserAttack(action);
	  // need to force userarea to redraw whenever target changes
	  ModuleEvent(EVENT_USERACTION, action, action_data);
      break;
   case A_ATTACKCLOSEST:
      if ((GetPlayerInfo()->viewID == 0) || (GetPlayerInfo()->viewID == GetPlayerInfo()->id))
         UserAttackClosest(action);
      break;

   case A_ENDSELECT:  /* Exit GAME_SELECT state, go back to GAME_PLAY state */
   case A_CURSOR_ESC:
	   if (UserMouselookIsEnabled())
	   {
			while (ShowCursor(FALSE) >= 0)
				ShowCursor(FALSE);
	   }
      if (GAME_PLAY == GameGetState())
	 UserMoveEsc();
      else
	 GameSetState(GAME_PLAY);
      break;

   case A_CURSORUP : 
      UserMoveCursor(A_CURSORUP, -CURSOR_JUMP, 0);
      break;
   case A_CURSORDOWN :
      UserMoveCursor(A_CURSORDOWN, CURSOR_JUMP, 0);
      break;
   case A_CURSORLEFT :
      UserMoveCursor(A_CURSORLEFT, 0, -CURSOR_JUMP);
      break;
   case A_CURSORRIGHT :
      UserMoveCursor(A_CURSORRIGHT, 0, CURSOR_JUMP);
      break;
   case A_CURSORUPLEFT : 
      UserMoveCursor(A_CURSORUPLEFT, -CURSOR_JUMP, -CURSOR_JUMP);
      break;
   case A_CURSORUPRIGHT :
      UserMoveCursor(A_CURSORUPRIGHT, -CURSOR_JUMP, CURSOR_JUMP);
      break;
   case A_CURSORDOWNLEFT :
      UserMoveCursor(A_CURSORDOWNLEFT, CURSOR_JUMP, -CURSOR_JUMP);
      break;
   case A_CURSORDOWNRIGHT :
      UserMoveCursor(A_CURSORDOWNRIGHT, CURSOR_JUMP, CURSOR_JUMP);
      break;

   case A_LOOK:
      UserLook();
      break;

   case A_LOOKINSIDE:
      UserLookInside();
      break;

   case A_LOOKMOUSE:
      UserLookMouseSquare();
      break;

   case A_PICKUP:
      UserPickup();
      break;

   case A_DROP:
      UserDrop();
      break;

   case A_PUT:
      UserPut();
      break;

   case A_APPLY:
      UserApply();
      break;

   case A_UNUSE:
      UserUnuse();
      break;

   case A_OFFER:
      UserMakeOffer();
      break;

   case A_GO:
      MoveUpdatePosition();   // Send our exact position, so that we try to go in right spot
      RequestGo();
      break;
      
   case A_TARGETCLEAR:
      if ((GetPlayerInfo()->viewID == 0) || (GetPlayerInfo()->viewID == GetPlayerInfo()->id))
	 SetUserTargetID( INVALID_ID );
      else
	 UserMoveEsc();
	  // need to force userarea to redraw whenever target changes
	  ModuleEvent(EVENT_USERACTION, action, action_data);
      // Fall through...
   case A_GOTOMAIN:  /* User pressed Escape; move focus to main menu */
      SetFocus(hMain);
      break;

   case A_GOTOSAY:   /* User pressed quote; move focus to text input box */
      TextInputSetFocus(True);  // Pretend that moving forward in window list; no harm here
      break;

   case A_SELECT:
	   if (UserMouselookIsEnabled())
	   {
			while (ShowCursor(FALSE) >= 0)
				ShowCursor(FALSE);
	   }
      UserSelect((ID) action_data);
      break;

   case A_BUY:
      UserBuy();
      break;

   case A_USE:
      UserUse();
      break;

   case A_STARTDRAG:
      UserStartDrag();
      break;

   case A_USERACTION:
      RequestAction((int) action_data);
      break;

   case A_MOUSEMOVE:
      UserMouseMove();
      break;

   case A_MAP:
     GraphicsToggleMap();

	   if (gD3DDriverProfile.bSoftwareRenderer == FALSE)
			D3DRenderEnableToggle();
      break;

   case A_LOOKUP:
      PlayerChangeHeight(+1);
      break;

   case A_LOOKDOWN:
      PlayerChangeHeight(-1);
      break;

   case A_LOOKSTRAIGHT:
      PlayerResetHeight();
      break;

   case A_QUIT:
      UserQuit();
      break;

   case A_HELP:
      StartHelp();
      break;

   case A_MAPZOOMIN:
      MapZoom(+1);
      break;

   case A_MAPZOOMOUT:
      MapZoom(-1);
      break;

   case A_TEXTINSERT:
      TextInputSetText((char *) action_data, True);
      break;

   case A_TEXTCOMMAND:
      TextInputSetText((char *) action_data, False);
      ParseGotText((char *) action_data);
      break;

   case A_WHO:
      UserWho();
      break;

   case A_FLIP:
      UserFlipPlayer();
      break;

   case A_ACTIVATEMOUSE:
      UserActivateMouse();
      break;

   case A_ACTIVATE:
      UserActivate();
      break;

   case A_CHANGEPASSWORD:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_PASSWORD), hMain, PasswordDialogProc);
      break;

   case A_TARGETPREVIOUS:
      UserTargetNextOrPrevious( False );
	  // need to force userarea to redraw whenever target changes
	  ModuleEvent(EVENT_USERACTION, action, action_data);
      break;

   case A_TARGETNEXT:
      UserTargetNextOrPrevious( True );
	  // need to force userarea to redraw whenever target changes
	  ModuleEvent(EVENT_USERACTION, action, action_data);
      break;

	case A_TARGETSELF:
		UserTargetSelf();
		// need to force userarea to redraw whenever target changes
	  ModuleEvent(EVENT_USERACTION, action, action_data);
	break;

	case A_MOUSELOOK:
		UserMouselookToggle();
		break;

#if 1
   case A_DEPOSIT:
      UserDeposit();
      break;

   case A_WITHDRAW:
      UserWithdraw();
      break;
#endif
   }
