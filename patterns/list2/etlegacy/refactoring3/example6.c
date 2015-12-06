switch (key)
	{
	case K_ESCAPE:
		CG_ShowHelp_Off(&cg.demohelpWindow);
		CG_keyOff_f();
		return;

	case K_TAB:
		if (down)
		{
			CG_ScoresDown_f();
		}
		else
		{
			CG_ScoresUp_f();
		}
		return;

	// Help info
	case K_BACKSPACE:
		if (!down)
		{
			if (cg.demohelpWindow != SHOW_ON)
			{
				CG_ShowHelp_On(&cg.demohelpWindow);
			}
			else
			{
				CG_ShowHelp_Off(&cg.demohelpWindow);
			}
		}
		return;

	// Screenshot keys
	case K_F11:
		if (!down)
		{
			trap_SendConsoleCommand(va("screenshot%s\n", ((cg_useScreenshotJPEG.integer) ? "JPEG" : "")));
		}
		return;
	case K_F12:
		if (!down)
		{
			CG_autoScreenShot_f();
		}
		return;

	// Window controls
	case K_SHIFT:
	case K_CTRL:
	case K_MOUSE4:
		cgs.fResize = down;
		return;
	case K_MOUSE1:
		cgs.fSelect = down;
		return;
#ifdef FEATURE_MULTIVIEW
	case K_MOUSE2:
		if (!down)
		{
			CG_mvSwapViews_f();             // Swap the window with the main view
		}
		return;
	case K_INS:
	case K_KP_PGUP:
		if (!down)
		{
			CG_mvShowView_f();              // Make a window for the client
		}
		return;
	case K_DEL:
	case K_KP_PGDN:
		if (!down)
		{
			CG_mvHideView_f();              // Delete the window for the client
		}
		return;
	case K_MOUSE3:
		if (!down)
		{
			CG_mvToggleView_f();            // Toggle a window for the client
		}
		return;
#endif
	// Third-person controls
	case K_ENTER:
		if (!down)
		{
			trap_Cvar_Set("cg_thirdperson", ((cg_thirdPerson.integer == 0) ? "1" : "0"));
		}
		return;
	case K_UPARROW:
		if (milli > cgs.thirdpersonUpdate)
		{
			float range = cg_thirdPersonRange.value;

			cgs.thirdpersonUpdate = milli + DEMO_THIRDPERSONUPDATE;
			range                -= ((range >= 4 * DEMO_RANGEDELTA) ? DEMO_RANGEDELTA : (range - DEMO_RANGEDELTA));
			trap_Cvar_Set("cg_thirdPersonRange", va("%f", range));
		}
		return;
	case K_DOWNARROW:
		if (milli > cgs.thirdpersonUpdate)
		{
			float range = cg_thirdPersonRange.value;

			cgs.thirdpersonUpdate = milli + DEMO_THIRDPERSONUPDATE;
			range                += ((range >= 120 * DEMO_RANGEDELTA) ? 0 : DEMO_RANGEDELTA);
			trap_Cvar_Set("cg_thirdPersonRange", va("%f", range));
		}
		return;
	case K_RIGHTARROW:
		if (milli > cgs.thirdpersonUpdate)
		{
			float angle = cg_thirdPersonAngle.value - DEMO_ANGLEDELTA;

			cgs.thirdpersonUpdate = milli + DEMO_THIRDPERSONUPDATE;
			if (angle < 0)
			{
				angle += 360.0f;
			}
			trap_Cvar_Set("cg_thirdPersonAngle", va("%f", angle));
		}
		return;
	case K_LEFTARROW:
		if (milli > cgs.thirdpersonUpdate)
		{
			float angle = cg_thirdPersonAngle.value + DEMO_ANGLEDELTA;

			cgs.thirdpersonUpdate = milli + DEMO_THIRDPERSONUPDATE;
			if (angle >= 360.0f)
			{
				angle -= 360.0f;
			}
			trap_Cvar_Set("cg_thirdPersonAngle", va("%f", angle));
		}
		return;

	// Timescale controls
	case K_KP_5:
	case K_KP_INS:
		if (!down)
		{
			trap_Cvar_Set("timescale", "1");
			cgs.timescaleUpdate = cg.time + 1000;
		}
		return;
	case K_SPACE:
		if (!down)
		{
			trap_SendConsoleCommand("pausedemo");
		}
		return;
	case K_KP_DOWNARROW:
		if (!down)
		{
			float tscale = cg_timescale.value;

			if (tscale <= 1.1f)
			{
				if (tscale > 0.1f)
				{
					tscale -= 0.1f;
				}
			}
			else
			{
				tscale -= 1.0;
			}
			trap_Cvar_Set("timescale", va("%f", tscale));
			cgs.timescaleUpdate = cg.time + (int)(1000.0f * tscale);
		}
		return;
	case K_MWHEELDOWN:
		if (!cgs.fKeyPressed[K_SHIFT])
		{
			if (!down)
			{
				CG_ZoomOut_f();
			}
			return;
		}       // Roll over into timescale changes
	case K_KP_LEFTARROW:
		if (!down && cg_timescale.value > 0.1f)
		{
			trap_Cvar_Set("timescale", va("%f", cg_timescale.value - 0.1f));
			cgs.timescaleUpdate = cg.time + (int)(1000.0f * cg_timescale.value - 0.1f);
		}
		return;
	case K_KP_UPARROW:
		if (!down)
		{
			trap_Cvar_Set("timescale", va("%f", cg_timescale.value + 1.0f));
			cgs.timescaleUpdate = cg.time + (int)(1000.0f * cg_timescale.value + 1.0f);
		}
		return;
	case K_MWHEELUP:
		if (!cgs.fKeyPressed[K_SHIFT])
		{
			if (!down)
			{
				CG_ZoomIn_f();
			}
			return;
		}       // Roll over into timescale changes
	case K_KP_RIGHTARROW:
		if (!down)
		{
			trap_Cvar_Set("timescale", va("%f", cg_timescale.value + 0.1f));
			cgs.timescaleUpdate = cg.time + (int)(1000.0f * cg_timescale.value + 0.1f);
		}
		return;

	// AVI recording controls
	case K_F1:
		if (down)
		{
			cgs.aviDemoRate = demo_avifpsF1.integer;
		}
		else
		{
			trap_Cvar_Set("cl_avidemo", demo_avifpsF1.string);
		}
		return;
	case K_F2:
		if (down)
		{
			cgs.aviDemoRate = demo_avifpsF2.integer;
		}
		else
		{
			trap_Cvar_Set("cl_avidemo", demo_avifpsF2.string);
		}
		return;
	case K_F3:
		if (down)
		{
			cgs.aviDemoRate = demo_avifpsF3.integer;
		}
		else
		{
			trap_Cvar_Set("cl_avidemo", demo_avifpsF3.string);
		}
		return;
	case K_F4:
		if (down)
		{
			cgs.aviDemoRate = demo_avifpsF4.integer;
		}
		else
		{
			trap_Cvar_Set("cl_avidemo", demo_avifpsF4.string);
		}
		return;
	case K_F5:
		if (down)
		{
			cgs.aviDemoRate = demo_avifpsF5.integer;
		}
		else
		{
			trap_Cvar_Set("cl_avidemo", demo_avifpsF5.string);
		}
		return;
	}
