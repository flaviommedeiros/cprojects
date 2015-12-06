switch (dropdownIndex) {
		case DDIDX_LOAD_GAME:
			game_do_command(0, 1, 0, 0, GAME_COMMAND_LOAD_OR_QUIT, 0, 0);
			break;
		case DDIDX_SAVE_GAME:
			tool_cancel();
			save_game();
			break;
		case DDIDX_SAVE_GAME_AS:
			if (RCT2_GLOBAL(RCT2_ADDRESS_SCREEN_FLAGS, uint8) & SCREEN_FLAGS_SCENARIO_EDITOR) {
				rct_s6_info *s6Info = (rct_s6_info*)0x0141F570;
				window_loadsave_open(LOADSAVETYPE_SAVE | LOADSAVETYPE_LANDSCAPE, s6Info->name);
			}
			else {
				tool_cancel();
				save_game_as();
			}
			break;
		case DDIDX_ABOUT:
			window_about_open();
			break;
		case DDIDX_OPTIONS:
			window_options_open();
			break;
		case DDIDX_SCREENSHOT:
			RCT2_GLOBAL(RCT2_ADDRESS_SCREENSHOT_COUNTDOWN, sint8) = 10;
			break;
		case DDIDX_GIANT_SCREENSHOT:
			screenshot_giant();
			break;
		case DDIDX_QUIT_TO_MENU:
			window_close_by_class(WC_MANAGE_TRACK_DESIGN);
			window_close_by_class(WC_TRACK_DELETE_PROMPT);
			game_do_command(0, 1, 0, 0, GAME_COMMAND_LOAD_OR_QUIT, 1, 0);
			break;
		case DDIDX_EXIT_OPENRCT2:
			rct2_quit();
			break;
#ifndef DISABLE_TWITCH
		case DDIDX_ENABLE_TWITCH:
			gTwitchEnable = !gTwitchEnable;
			break;
#endif
		}
