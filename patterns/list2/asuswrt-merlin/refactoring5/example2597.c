#ifdef WEB_REDIRECT
if(nvram_get_int("freeze_duck"))
		_dprintf("\n<**>freeze the duck, %ds left!\n", nvram_get_int("freeze_duck"));	// don't check conn state during inner events period
	else
#endif
	if(cross_state == DISCONN){
		csprintf("\n# Enable direct rule\n");
		rule_setup = 1;
	}
	else if(cross_state == CONNED && isFirstUse){
		csprintf("\n#CONNED : Enable direct rule\n");
		rule_setup = 1;
	}
