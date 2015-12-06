#ifndef DEDICATED
if (uivm)
		{
			uiMenuCommand_t currentMenu = VM_Call(uivm, UI_GET_ACTIVE_MENU);
			if (currentMenu != UIMENU_WM_AUTOUPDATE)
			{
				VM_Call(uivm, UI_SET_ACTIVE_MENU, UIMENU_WM_AUTOUPDATE);
			}
		}
		else
#endif
		{
			Com_Printf("%s ^1RUN UPDATE COMMAND TO UPDATE\n", com_updatemessage->string);
		}
