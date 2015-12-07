switch(select)
	{
	case iAbout:
		mac_AboutBox();
		return;
	case iOpen:
		StandardGetFile(0, -1, 0, &stdReply);
		if (stdReply.sfGood)
		{
			mac_add_fsspec(&stdReply.sfFile);
		}
		return;
	case iClose:
		CloseFrontWindow();
		return;

	case iLogWindow:	SHOW_WINDOW(mac_LogWindow);		return;
	case iListWindow:	SHOW_WINDOW(mac_ListWindow);	return;
	case iWrdWindow:	SHOW_WINDOW(mac_WrdWindow);		return;
	case iDocWindow:	SHOW_WINDOW(mac_DocWindow);		return;
	case iSpecWindow:
#ifdef SUPPORT_SOUNDSPEC
		if(!mac_SpecWindow.show)
		{
			mac_SpecWindow.show=true;
		    open_soundspec();
  			soundspec_update_wave(NULL, 0);
		}
		SelectWindow(mac_SpecWindow.ref);
#endif /* SUPPORT_SOUNDSPEC */
		return;
	case iTraceWindow:	SHOW_WINDOW(mac_TraceWindow);	return;
	case iSkinWindow: SHOW_WINDOW(mac_SkinWindow); return;
	case iSaveAs:
		NewThread(kCooperativeThread, ConvertToAiffFile,
	         0, 0, kCreateIfNeeded, 0, 0);
		return;
		
	case iPref:	mac_SetPlayOption(); return;
	case iQuit:	Do_Quit();			 return;
	
	//Play menu
	case iPlay:	SKIN_ACTION_PLAY(); break;
	case iStop:	SKIN_ACTION_STOP();	break;
	case iPause:	SKIN_ACTION_PAUSE(); break;
	case iPrev:	SKIN_ACTION_PREV(); break;
	case iNext:	SKIN_ACTION_NEXT(); break;
	
		//Synth menu
	case iTiMidity:{
		MenuHandle menu=GetMenu(mSynth);
		CheckItem(menu, iTiMidity & 0x0000FFFF, 1);
		CheckItem(menu, iQuickTime & 0x0000FFFF, 0);
		CheckItem(menu, iOMS & 0x0000FFFF, 0);
		play_mode=&mac_play_mode;
		}
		return;
	case iQuickTime:{
		MenuHandle menu=GetMenu(mSynth);
		
		if( mac_quicktime_play_mode.fd==-1 ){ //not opened yet
			if( mac_quicktime_play_mode.open_output()!=0 ){
				SysBeep(0);
				return;	//can't open device
			}
		}
		CheckItem(menu, iTiMidity & 0x0000FFFF, 0);
		CheckItem(menu, iQuickTime & 0x0000FFFF, 1);
		CheckItem(menu, iOMS & 0x0000FFFF, 0);
		play_mode=&mac_quicktime_play_mode;
		}
		return;
#ifdef MAC_USE_OMS
	case iOMS:{
		MenuHandle menu=GetMenu(mSynth);
		
		if( mac_oms_play_mode.fd==-1 || (modifiers & optionKey) ){
			if( mac_oms_play_mode.open_output()!=0 ){
				SysBeep(0);
				return;	//can't open device
			}
		}
		CheckItem(menu, iTiMidity & 0x0000FFFF, 0);
		CheckItem(menu, iQuickTime & 0x0000FFFF, 0);
		CheckItem(menu, iOMS & 0x0000FFFF, 1);
		play_mode=&mac_oms_play_mode;
		}
		return;
#endif
	}
