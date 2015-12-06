switch (keysym->sym)
		{
		// keypad
		case SDLK_KP_0:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_INS;
			}
			break;
		case SDLK_KP_1:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_END;
			}
			break;
		case SDLK_KP_2:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_DOWNARROW;
			}
			break;
		case SDLK_KP_3:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_PGDN;
			}
			break;
		case SDLK_KP_4:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_LEFTARROW;
			}
			break;
		case SDLK_KP_5:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_5;
			}
			break;
		case SDLK_KP_6:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_RIGHTARROW;
			}
			break;
		case SDLK_KP_7:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_HOME;
			}
			break;
		case SDLK_KP_8:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_UPARROW;
			}
			break;
		case SDLK_KP_9:
			if (!(keysym->mod & KMOD_NUM))
			{
				key = K_KP_PGUP;
			}
			break;
		case SDLK_KP_ENTER:     key = K_KP_ENTER;
			break;
		case SDLK_KP_PERIOD:    key = K_KP_DEL;
			break;
		case SDLK_KP_MULTIPLY:  key = K_KP_STAR;
			break;
		case SDLK_KP_PLUS:      key = K_KP_PLUS;
			break;
		case SDLK_KP_MINUS:     key = K_KP_MINUS;
			break;
		case SDLK_KP_DIVIDE:    key = K_KP_SLASH;
			break;

		case SDLK_PAGEUP:       key = K_PGUP;
			break;
		case SDLK_PAGEDOWN:     key = K_PGDN;
			break;
		case SDLK_HOME:         key = K_HOME;
			break;
		case SDLK_END:          key = K_END;
			break;
		case SDLK_LEFT:         key = K_LEFTARROW;
			break;
		case SDLK_RIGHT:        key = K_RIGHTARROW;
			break;
		case SDLK_DOWN:         key = K_DOWNARROW;
			break;
		case SDLK_UP:           key = K_UPARROW;
			break;
		case SDLK_ESCAPE:       key = K_ESCAPE;
			break;
		case SDLK_RETURN:       key = K_ENTER;
			break;
		case SDLK_TAB:          key = K_TAB;
			break;
		case SDLK_F1:           key = K_F1;
			break;
		case SDLK_F2:           key = K_F2;
			break;
		case SDLK_F3:           key = K_F3;
			break;
		case SDLK_F4:           key = K_F4;
			break;
		case SDLK_F5:           key = K_F5;
			break;
		case SDLK_F6:           key = K_F6;
			break;
		case SDLK_F7:           key = K_F7;
			break;
		case SDLK_F8:           key = K_F8;
			break;
		case SDLK_F9:           key = K_F9;
			break;
		case SDLK_F10:          key = K_F10;
			break;
		case SDLK_F11:          key = K_F11;
			break;
		case SDLK_F12:          key = K_F12;
			break;
		case SDLK_F13:          key = K_F13;
			break;
		case SDLK_F14:          key = K_F14;
			break;
		case SDLK_F15:          key = K_F15;
			break;
		case SDLK_BACKSPACE:    key = K_BACKSPACE;
			break;

		case SDLK_DELETE:       key = K_DEL;
			break;
		case SDLK_PAUSE:        key = K_PAUSE;
			break; // FIXME: SDL 2.0 maps PAUSE to PAUSE as well as BREAK
		// (key = K_BREAK;         break;)
		case SDLK_LSHIFT:
		case SDLK_RSHIFT:       key = K_SHIFT;
			break;
		case SDLK_LCTRL:
		case SDLK_RCTRL:        key = K_CTRL;
			break;

#ifdef __APPLE__
		case SDLK_RGUI:
		case SDLK_LGUI:         key = K_COMMAND;
			break;
#else
		case SDLK_RGUI:
		case SDLK_LGUI:         key = K_SUPER;
			break;
#endif

		case SDLK_RALT:
		case SDLK_LALT:         key = K_ALT;
			break;

		case SDLK_INSERT:       key = K_INS;
			break;

		case SDLK_MODE:         key = K_MODE;
			break;
		case SDLK_APPLICATION:  key = K_COMPOSE;     // map to K_MENU ?
			break;
		case SDLK_HELP:         key = K_HELP;
			break;
		case SDLK_PRINTSCREEN:  key = K_PRINT;
			break;
		case SDLK_SYSREQ:       key = K_SYSREQ;
			break;
		case SDLK_MENU:         key = K_MENU;
			break;
		case SDLK_POWER:        key = K_POWER;
			break;
		case SDLK_CURRENCYUNIT: key = K_EURO;
			break;
		case SDLK_UNDO:         key = K_UNDO;
			break;
		case SDLK_SCROLLLOCK:   key = K_SCROLLOCK;
			break;
		case SDLK_NUMLOCKCLEAR: key = K_KP_NUMLOCK;
			break;
		case SDLK_CAPSLOCK:     key = K_CAPSLOCK;
			break;

		default:
			// physical key mapped to a non-ascii character
			switch (keysym->scancode)
			{
			case SDL_SCANCODE_1: key = K_1;
				break;
			case SDL_SCANCODE_2: key = K_2;
				break;
			case SDL_SCANCODE_3: key = K_3;
				break;
			case SDL_SCANCODE_4: key = K_4;
				break;
			case SDL_SCANCODE_5: key = K_5;
				break;
			case SDL_SCANCODE_6: key = K_6;
				break;
			case SDL_SCANCODE_7: key = K_7;
				break;
			case SDL_SCANCODE_8: key = K_8;
				break;
			case SDL_SCANCODE_9: key = K_9;
				break;
			case SDL_SCANCODE_0: key = K_0;
				break;

			case SDL_SCANCODE_MINUS: key = K_MINUS;
				break;
			case SDL_SCANCODE_EQUALS: key = K_EQUALS;
				break;
			case SDL_SCANCODE_LEFTBRACKET: key = K_LEFTBRACKET;
				break;
			case SDL_SCANCODE_RIGHTBRACKET: key = K_RIGHTBRACKET;
				break;
			case SDL_SCANCODE_BACKSLASH: key = K_BACKSLASH;
				break;
			case SDL_SCANCODE_SEMICOLON: key = K_SEMICOLON;
				break;
			case SDL_SCANCODE_APOSTROPHE: key = K_APOSTROPHE;
				break;
			case SDL_SCANCODE_GRAVE: key = K_GRAVE;              // NOTE: this is console toogle key!
				break;
			case SDL_SCANCODE_COMMA: key = K_COMMA;
				break;
			case SDL_SCANCODE_PERIOD: key = K_PERIOD;
				break;
			case SDL_SCANCODE_SLASH: key = K_SLASH;
				break;
			case SDL_SCANCODE_NONUSBACKSLASH: key = K_NONUSBACKSLASH;
				break;

			default:
				break;
			}
			break;
		}
